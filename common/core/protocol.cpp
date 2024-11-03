#include "./protocol.h"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

// Para htons y ntohs
#include <arpa/inet.h>

#include "common/core/liberror.h"

Protocol::Protocol(Messenger& _messenger): messenger(_messenger), active(true) {}

// Protocol::Protocol(Messenger* _messenger): messenger(*_messenger), active(true) {}

// Protocol::Protocol(): messenger(), active(false) {}
// Protocol::Protocol(std::unique_ptr<Messenger>& _messenger):
//         messenger(std::move(_messenger)), active(messenger.get() != NULL) {}
//  Para asegurarse del scope de la variable hay que pasarlo al heap.
// Protocol::Protocol(Socket& _skt): messenger(new Socket(std::move(_skt))), active(true) {}

/*
Protocol::Protocol(Protocol&& other):
        messenger(other.messenger), active(other.active.load()) {
    // Reset/close del otro.
    //other.messenger.reset(NULL);
    other.active = false; // Manejamos asi para que no haya dramas de ownership.
}

Protocol& Protocol::operator=(Protocol&& other) {
    if (this == &other) {
        return *this;
    }

    this->messenger = other.messenger;
    //this->messenger = std::move(other.messenger);  // El ptr le quita owner ship al otro
    this->active = other.active.load();

    // Reset/close del otro.
    //other.messenger.reset(NULL);
    other.active = false;

    return *this;
}

*/


uint16_t Protocol::recvshort() {
    uint16_t num;
    if (this->messenger.tryrecvall(&num, 2) != 2) {  // Intenta leer los 2 bytes.
        throw LibError(1, "Read of length failed read less than 2 byte");
    }
    return ntohs(num);  // castea a host endiannes.
}

void Protocol::sendshort(const uint16_t num) {
    uint16_t size = htons(num);  // Aserveramos big endian.
    // Envio del size del mensaje a mandar
    if (this->messenger.trysendall(&size, 2) != 2) {
        throw LibError(1, "Failed to send of short.");
    }
}


// Lee todo el mensaje aseguradamente. Y le pone un 0 al final. Para hacer facil la conversion a
// string.
std::vector<char> Protocol::recvmsg() {
    uint16_t recvlen = recvshort();

    std::vector<char> res(recvlen + 1, 0);

    // Puede ser empty string, que no deberia perse pero no es para nosotros decir es error.
    if (recvlen > 0) {
        this->messenger.recvall(res.data(), recvlen);
    }

    return res;
}

std::string Protocol::recvmsgstr() { return std::string(recvmsg().data()); }

uint16_t Protocol::recvmsg(char* buff, unsigned int max) {
    uint16_t recvlen = recvshort();
    if (recvlen == 0) {
        return 0;  // Algun empty string, que no deberia perse pero no es para nosotros decir es
                   // error.
    }

    if (recvlen > max) {  // Cannot receive it!
        throw LibError(1, "Buffer overflow, %d is the max length, connection received %d", max,
                       recvlen);
    }

    if (this->messenger.tryrecvall(buff, recvlen) < recvlen) {  // Fallo al leer todo el mensaje!
        throw LibError(1, "Expected to receive %d but eof reached or read failed", recvlen);
    }

    return recvlen;
}

void Protocol::sendmsg(const char* buff, const uint16_t len) {
    sendshort(len);
    this->messenger.sendall(buff, len);  // Envio del mensaje en si
}
void Protocol::sendmsg(const std::string& message) {
    this->sendmsg(message.c_str(), message.length());
}


void Protocol::sendbyte(const uint8_t num) {
    if (this->messenger.trysendall(&num, 1) == 0) {
        throw LibError(1,  // default para errores
                       "Failed to send u8 number to connection");
    }
}

// Simplemente para no enviar multiples sendbyte.
// No es el envio de un mensaje. Que tiene el envio del len pre mensaje.
// Sirve para mandar structs.
void Protocol::sendbytes(const void* msg, const unsigned int count) {
    this->messenger.sendall(msg, count);
}

void Protocol::recvbytes(void* buff, const unsigned int count) {
    this->messenger.recvall(buff, count);
}
bool Protocol::tryrecvbytes(void* buff, const unsigned int count) {
    return this->messenger.tryrecvall(buff, count) == count;
}

uint8_t Protocol::recvbyte() {
    uint8_t res;
    if (this->messenger.tryrecvall(&res, 1) == 0) {
        throw LibError(1,  // default para errores
                       "Failed to recv u8 number from connection");
    }

    return res;
}

bool Protocol::tryrecvbyte(uint8_t* out) {
    if (this->messenger.tryrecvall(out, 1) == 0) {
        return false;
    }
    return true;
}


bool Protocol::isactive() { return active.load(); }

// Estando o no en null.
// Simplemente llama al destructor
void Protocol::close() {
    if (active.exchange(false)) {

        // Esto que seria llamado en el destructor tambien
        // Cerraria el messenger.
        messenger.finish();

        // Se podria setear a null. Pero daria segmentation fault.
        // Y tampoco se quiere verificar con ifs si es active.
        // messenger.reset(NULL);
    }
}
