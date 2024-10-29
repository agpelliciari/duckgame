#include "./queuesocket.h"

#include <cstring>
#include <iostream>

#include "common/core/liberror.h"

QueueSocket::QueueSocket(int _size, bool _canexpand):
        buffer(), closed(false), canexpand(_canexpand), size(_size), offsetRead(0), offsetWrite(0) {
    buffer.reserve(size);
}


void QueueSocket::chktOpen() const {
    if (closed) {
        throw std::runtime_error("socket with invalid file descriptor (-1), "
                                 "perhaps you are using a *previously moved* "
                                 "socket (and therefore invalid).");
    }
}

void QueueSocket::seek(int pos) { this->offsetRead = pos; }
void QueueSocket::reset() {  // Resetea 'borra' toda la informacion. Setea ambos offsets a 0.
    this->offsetRead = 0;
    this->offsetWrite = 0;
}

// Enviar la cantidad especificada, pero puede que mande/reciba menos.
int QueueSocket::sendsome(const void* data, unsigned int sz) {
    unsigned int canSend = size - offsetWrite;

    if (sz < canSend) {
        canSend = sz;
    }

    if (canSend == 0) {
        return 0;
    }

    // cppcheck-suppress cstyleCast
    std::memcpy(buffer.data() + offsetWrite, (const char*)data, canSend);
    offsetWrite += canSend;
    return canSend;
}
unsigned int QueueSocket::recvsome(void* data, unsigned int sz) {
    unsigned int canRecv = offsetWrite - offsetRead;  // Solo puede leer hasta donde se escribio!
    if (sz < canRecv) {
        canRecv = sz;
    }
    if (canRecv == 0) {
        return 0;
    }

    // cppcheck-suppress cstyleCast
    std::memcpy((char*)data, (buffer.data() + offsetRead), canRecv);
    offsetRead += canRecv;
    return canRecv;
}

// Intenta enviar todo y devuelve lo que envio/ tira excepcion
unsigned int QueueSocket::trysendall(const void* data, unsigned int sz) {
    chktOpen();

    int overflow = sz - (size - offsetWrite);
    std::cout << "SENDING ON QUEUE SOCKET " << (int)sz << " OVERFLOW " << overflow << std::endl;
    if (overflow > 0 && canexpand) {
        size += overflow;
        buffer.reserve(size);  // Expand buffer.
    }

    return sendsome(data, sz);
}
void QueueSocket::sendall(const void* data, unsigned int sz) {
    unsigned int sent = trysendall(data, sz);
    if (sent != sz) {
        throw LibError(EPIPE, "socket sent only %d of %d bytes", sent, sz);
    }
}

// Intenta leer lo maximo que pueda, a lo sumo sz. Retorna la cantidad leida.
unsigned int QueueSocket::tryrecvall(void* data, unsigned int sz) {
    chktOpen();
    std::cout << "RECV ON QUEUE SOCKET " << (int)sz << std::endl;
    return recvsome(data, sz);  // No hay logica para 'esperar' a que llege mas data.
}

// Intenta leer sz bytes. Tira excepcion sino lee todo.
void QueueSocket::recvall(void* data, unsigned int sz) {
    unsigned int read = tryrecvall(data, sz);

    if (read < sz) {  // No se leyo todo.
        throw LibError(EPIPE, "socket received only %d of %d bytes", read, sz);
    }
}

// Cierra parcial o completamente. Es no except. Devuelve -1 si fallo.
int QueueSocket::shutdown(int how) {
    std::cout << "SHUTDOWN QUEUE SOCKET? " << how << std::endl;
    return closed ? -1 : 0;
}

// Cierra el socket. Aunque no necesariamente haria el shutdown.
int QueueSocket::close() {
    if (closed) {
        return -1;
    }

    closed = true;
    return 0;
}

QueueSocket::~QueueSocket() {}
