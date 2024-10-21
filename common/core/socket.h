#ifndef SOCKET_H
#define SOCKET_H

#include "./messenger.h"
/*
 * TDA Socket.
 * Por simplificación este TDA se enfocará solamente
 * en sockets IPv4 para TCP.
 * */
class Socket: public Messenger {
private:
    // Si son usadas. cppcheck..
    // cppcheck-suppress unusedStructMember
    int skt;

    // cppcheck-suppress unusedStructMember
    bool closed;

    explicit Socket(int skt);

    void chk_skt_or_fail() const;

public:
    // Constructor para un socket que busca conectarse al host y serv. Si hay error al conectar tira
    // excepcion.
    Socket(const char* hostname, const char* servname);

    // Constructor para un socket que busca bindearse en un serv local. Normalmente para servers.
    explicit Socket(const char* servname);

    // No tiene sentido querer hacer copias. O generaria muchos problemas tener de sockets al mismo
    // fd.
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    // Para hacerlo movible
    Socket(Socket&&);
    Socket& operator=(Socket&&);


    // Wrappers para syscalls de recv y send. Que intentan recibir/enviar a lo sumo sz.
    // Pero pueden ser menos. Siempre mas que 0, 0 si hay un EPIPE. Si hubiera un error distinto,
    // tira excepcion. No se devuelve negativos.
    int sendsome(const void* data, unsigned int sz) override;
    unsigned int recvsome(void* data,
                          unsigned int sz) override;  // En caso de error -1.. Tira excepcion.

    // Send all itera hasta que, exactamente sz bytes fueron enviados. Si se envian menos queda en
    // el caller decidir
    unsigned int trysendall(const void* data, unsigned int sz) override;
    void sendall(const void* data,
                 unsigned int sz) override;  // Intenta enviar todo. Sino tira excepcion.

    // Intenta leer lo maximo que pueda, a lo sumo sz. Retorna la cantidad leida.
    unsigned int tryrecvall(void* data, unsigned int sz) override;

    // Intenta leer sz bytes. Tira excepcion sino lee todo.
    void recvall(void* data, unsigned int sz) override;

    // Acepta una conexión entrante y retorna un nuevo socket, si falla tira excepcion.
    Socket accept();

    // Cierra parcial o completamente. Es no except. Devuelve -1 si fallo.
    int shutdown(int how) override;

    // Cierra el socket. Aunque no necesariamente haria el shutdown.
    int close() override;

    // Destructor, se encarga de llamar al shutdown si no lo fue.
    ~Socket();
};
#endif
