#include "./simplemessenger.h"

#include <cstring>
#include <iostream>

#include "common/core/liberror.h"

SimpleMessenger::SimpleMessenger(int _cap, bool _canexpand):
        buffer(), closed(false), canexpand(_canexpand), cap(_cap), offsetRead(0), offsetWrite(0) {
    buffer.reserve(cap);
}


int SimpleMessenger::size() const{
     return offsetWrite - offsetRead;
}
const char * SimpleMessenger::first() const{
     return buffer.data()+offsetRead;
}

void SimpleMessenger::chktOpen() const {
    if (closed) {
        throw std::runtime_error("socket with invalid file descriptor (-1), "
                                 "perhaps you are using a *previously moved* "
                                 "socket (and therefore invalid).");
    }
}

void SimpleMessenger::seek(int pos) { this->offsetRead = pos; }
void SimpleMessenger::reset() {  // Resetea 'borra' toda la informacion. Setea ambos offsets a 0.
    this->offsetRead = 0;
    this->offsetWrite = 0;
}

// Enviar la cantidad especificada, pero puede que mande/reciba menos.
int SimpleMessenger::sendsome(const void* data, unsigned int sz) {
    unsigned int canSend = cap - offsetWrite;

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
unsigned int SimpleMessenger::recvsome(void* data, unsigned int sz) {
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
unsigned int SimpleMessenger::trysendall(const void* data, unsigned int sz) {
    chktOpen();

    int overflow = sz - (cap - offsetWrite);
    if (overflow > 0 && canexpand) {
        // No se puede usar ni resize ni reserve... ya que tiran la data actual...
        // Por lo que no queda otra, que crear uno nuevo, copiar lo existente y swapear.

        std::vector<char> newone;
        newone.reserve(cap + overflow);  // Expand buffer.
        std::memcpy(newone.data(), buffer.data(), cap);
        cap += overflow;
        std::swap(buffer, newone);
    }

    return sendsome(data, sz);
}
void SimpleMessenger::sendall(const void* data, unsigned int sz) {
    unsigned int sent = trysendall(data, sz);
    if (sent != sz) {
        throw LibError(EPIPE, "socket sent only %d of %d bytes", sent, sz);
    }
}

// Intenta leer lo maximo que pueda, a lo sumo sz. Retorna la cantidad leida.
unsigned int SimpleMessenger::tryrecvall(void* data, unsigned int sz) {
    chktOpen();
    return recvsome(data, sz);  // No hay logica para 'esperar' a que llege mas data.
}

// Intenta leer sz bytes. Tira excepcion sino lee todo.
void SimpleMessenger::recvall(void* data, unsigned int sz) {
    unsigned int read = tryrecvall(data, sz);

    if (read < sz) {  // No se leyo todo.
        throw LibError(EPIPE, "socket received only %d of %d bytes", read, sz);
    }
}

// Cierra el socket
int SimpleMessenger::finish() {
    if (closed) {
        return -1;
    }

    closed = true;
    return 0;
}

SimpleMessenger::~SimpleMessenger() {}
