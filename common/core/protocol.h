#ifndef LIB_PROTOCOL_H
#define LIB_PROTOCOL_H

#include <atomic>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "common/core/messenger.h"

// Se incluye socket. Para abstraer si es una copia en el heap o no.
//#include "common/core/socket.h"

// Clase protocol, interfaz directa con el socket. Y proporciona los acciones base
// como lo es mandar un mensaje, numero o string.

// En general que hace cada cosa es bastante descriptivo.
// Como pre condicion esta simplemente que el socket este abierto. Tira excepcion si no.
// A menos que sea el recvsignal. Que el eof seria en si una.
class Protocol {
protected:
    // Para poder aplicar polimorfismo...
    Messenger& messenger;
    std::atomic<bool> active;

public:
    // explicit Protocol(Messenger* _messenger);  // Desde un messenger cualquiera
    // explicit Protocol(std::unique_ptr<Messenger>& _messenger);

    // Para abstraer que hace con el socket en si.
    explicit Protocol(Messenger& _messenger);

    // Asumamos por ahora que no se quiere permitir copias..
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    Protocol(Protocol&&) = delete;
    Protocol& operator=(Protocol&&) = delete;

    bool isactive();  // Se fija si esta activo, pudo ser cerrado como nunca haber sido activo.
    void close();

    // Byte communicaiton!!
    void sendbyte(const uint8_t byte);
    uint8_t recvbyte();

    // Short communication!!
    uint16_t recvshort();
    void sendshort(const uint16_t num);

    unsigned int recvuint();
    void senduint(const unsigned int num);


    // para mandar structs.. o similes, cuando se sabe la longitud.
    void sendbytes(const void* msg, const unsigned int count);
    void recvbytes(void* buff, const unsigned int count);

    // Para flags o condicionales.
    bool tryrecvbytes(void* buff, const unsigned int count);
    bool tryrecvbyte(uint8_t* out);

    // Para mensajes i.e cuando el que recibe no sabe la longitud.
    void sendmsg(const char* buff, const uint16_t len);
    void sendmsg(const std::string& message);


    uint16_t recvmsg(char* buff,
                     const unsigned int max);  // attemps read msg, throws exception if len > max
    // attemps read message of chars. Uses vector to store the len.
    std::vector<char> recvmsg();
    std::string recvmsgstr();
};
#endif
