#include "./socket.h"

#include <stdexcept>

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "./liberror.h"
#include "./resolver.h"

Socket::Socket(const char* hostname, const char* servname) {
    Resolver resolver(hostname, servname, false);

    int s = -1;
    skt = -1;
    this->closed = true;

    /*
     * Por cada dirección obtenida tenemos que ver cual es realmente funcional.
     * `getaddrinfo` puede darnos direcciones IP validas pero que apuntan
     * a servidores que no están activos (`getaddrinfo` simplemente no
     * lo puede saber).
     *
     * Es responsabilidad nuestra probar cada una de ellas hasta encontrar
     * una que funcione.
     * */
    while (resolver.has_next()) {
        struct addrinfo* addr = resolver.next();

        /* Cerramos el socket si nos quedo abierto de la iteración
         * anterior
         * */
        if (skt != -1)
            ::close(skt);

        /*
         * Con esta llamada creamos/obtenemos un socket.
         * */
        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            continue;
        }

        /* Intentamos conectarnos al servidor cuya dirección
         * fue dada por `getaddrinfo`
         *
         * Esta operación es **bloqueante** lo que significa que el programa
         * va a detenerse unos momentos hasta poder conectarse al server
         * o detectar y notificar de un error.
         * */
        s = connect(skt, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }


        this->closed = false;
        return;
    }

    /*
     * Si terminamos el while-loop es por que no nos pudimos
     * conectar.
     * */
    int saved_errno = errno;
    if (skt != -1)
        ::close(skt);
    skt = -1;  // reset

    throw LibError(saved_errno, "socket construction failed (connect to %s:%s)",
                   (hostname ? hostname : ""), (servname ? servname : ""));
}

Socket::Socket(const char* servname) {
    Resolver resolver(nullptr, servname, true);

    int s = -1;
    skt = -1;
    this->closed = true;
    while (resolver.has_next()) {
        struct addrinfo* addr = resolver.next();

        if (skt != -1)
            ::close(skt);

        skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (skt == -1) {
            continue;
        }

        /*
         * Configuramos al socket para q no falle si la dirección local
         **/
        int optval = 1;
        s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        if (s == -1) {
            continue;
        }

        /*
         * Hacemos le bind: enlazamos el socket a una dirección local.
         * A diferencia de lo que hacemos en `Socket::init_for_connection`
         * que obtenemos una dirección de una máquina remota y nos conectamos
         * a ella, el resolver nos dará direcciones locales (véase el flag
         * `is_passive` de `Resolver`).
         *
         * Con `bind` asociaremos el socket a dicha dirección local
         * y con `listen` pondremos el socket a escuchar conexiones entrantes.
         * */
        s = bind(skt, addr->ai_addr, addr->ai_addrlen);
        if (s == -1) {
            continue;
        }

        s = listen(skt, 20);
        if (s == -1) {
            continue;
        }

        this->closed = false;
        return;
    }

    int saved_errno = errno;

    if (skt != -1)
        ::close(skt);

    throw LibError(saved_errno, "socket construction failed (listen on %s)",
                   (servname ? servname : ""));
}

Socket::Socket(Socket&& other) {
    /* Nos copiamos del otro socket... */
    this->skt = other.skt;
    this->closed = other.closed;

    // Y le sacas el ownership para evitar problemas.
    other.skt = -1;
    other.closed = true;
}

Socket& Socket::operator=(Socket&& other) {
    if (this == &other)  // Tambien para el mov.
        return *this;

    if (not this->closed) {  // Cerrate ya que vas a usar el socket del otro.
        ::shutdown(this->skt, 2);
        ::close(this->skt);
    }

    /* Ahora hacemos los mismos pasos que en el move constructor */
    this->skt = other.skt;
    this->closed = other.closed;
    other.skt = -1;
    other.closed = true;

    return *this;
}
// cppcheck-suppress cstyleCast
unsigned int Socket::recvsome(void* data, unsigned int sz) {
    chk_skt_or_fail();
    // cppcheck-suppress cstyleCast
    int s = recv(this->skt, (char*)data, sz, 0);

    if (s < 0) {
        throw LibError(errno, "socket recvsome failed");
    }

    return s;  //>= 0
}

int Socket::sendsome(const void* data, unsigned int sz) {
    chk_skt_or_fail();
    // cppcheck-suppress cstyleCast
    int s = send(this->skt, (char*)data, sz, MSG_NOSIGNAL);
    if (s == -1) {
        // EOF/Broken pipe.
        if (errno == EPIPE) {  // EPIPE significa se cerro la conexion. EOF escencialmente. Si eso
                               // es un error no se sabe
            return 0;
        }
        throw LibError(errno, "socket send failed");
    }
    return s;
}

unsigned int Socket::tryrecvall(void* data, unsigned int sz) {
    unsigned int read = recvsome((char*)data,  // cppcheck-suppress cstyleCast
                                 sz);
    unsigned int total = read;

    while (total < sz && read > 0) {

        read = recvsome((char*)data + total,  // cppcheck-suppress cstyleCast
                        sz - total);
        // Suma lo leido.
        total += read;
    }

    // EOF o leyo todo... el tirar excepcion si no se llego al total. Es
    // trabajo de otro:: recvall.
    return total;
}

void Socket::recvall(void* data, unsigned int sz) {
    if (tryrecvall(data, sz) < sz) {  // No se leyo todo.
        throw LibError(EPIPE, "socket received only %d of %d bytes", read, sz);
    }
}

unsigned int Socket::trysendall(const void* data, unsigned int sz) {
    if (sz == 0) {  // Solo por las dudas.
        return 0;
    }

    int sent = sendsome((char*)data,  // cppcheck-suppress cstyleCast
                        sz);
    unsigned int total = 0;
    while (total < sz && sent > 0) {
        total += sent;
        sent = sendsome((char*)data + total,  // cppcheck-suppress cstyleCast
                        sz - total);
    }
    return total;
}
void Socket::sendall(const void* data, unsigned int sz) {
    unsigned int sent = trysendall(data, sz);
    if (sent != sz) {  // send all asevera se envio todo. O falla.
        throw LibError(EPIPE, "socket sent only %d of %d bytes", sent, sz);
    }
}


Socket::Socket(int skt) {
    this->skt = skt;
    this->closed = false;
}

Socket Socket::accept() {
    chk_skt_or_fail();
    /*
     * `accept` nos bloqueara hasta que algún cliente se conecte a nosotros
     * y la conexión se establezca.
     *
     * Una vez que eso suceda, `accept` retornara el file descriptor
     * de un *nuevo* socket (`peer_skt`) que representara a la
     * conexión establecida con *ese* cliente.
     *
     * En todo momento podemos seguir usando *nuestro* file descriptor
     * (`this->skt`) para seguir haciendo más llamadas a `accept`
     * independientemente de que enviemos/recibamos del socket `peer`.
     * */
    int peer_skt = ::accept(this->skt, nullptr, nullptr);
    if (peer_skt == -1)
        throw LibError(errno, "socket accept failed");

    /*
     * `peer_skt` es un file descriptor crudo y no queremos
     * que nuestro cliente manipule recursos crudos sino que
     * los use a través de un TDA.
     *
     * Por eso creamos un `Socket` y lo pasamos por movimiento
     * */
    return Socket(peer_skt);
}

int Socket::shutdown(int how) {
    chk_skt_or_fail();
    return ::shutdown(this->skt, how);
}

int Socket::close() {
    chk_skt_or_fail();
    this->closed = true;
    return ::close(this->skt);
}

Socket::~Socket() {
    if (not this->closed) {
        ::shutdown(this->skt, 2);
        ::close(this->skt);
    }
}

void Socket::chk_skt_or_fail() const {
    if (skt == -1) {
        throw std::runtime_error("socket with invalid file descriptor (-1), "
                                 "perhaps you are using a *previously moved* "
                                 "socket (and therefore invalid).");
    }
}
