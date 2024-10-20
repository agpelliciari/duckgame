#ifndef LIB_PROTOCOL_H
#define LIB_PROTOCOL_H

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "./socket.h"

// Clase protocol, interfaz directa con el socket. Y proporciona los acciones base
// como lo es mandar un mensaje, numero o string.

// En general que hace cada cosa es bastante descriptivo.
// Como pre condicion esta simplemente que el socket este abierto. Tira excepcion si no.
// A menos que sea el recvsignal. Que el eof seria en si una.
class Protocol {
protected:
    // Para poder aplicar polimorfismo...
    std::unique_ptr<Socket> skt;

    // Socket skt;

public:
    explicit Protocol(Socket& _skt);
    explicit Protocol(Socket* _skt);
    explicit Protocol(std::unique_ptr<Socket>& _skt);

    // Asumamos por ahora que no se quiere permitir copias..
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    Protocol(Protocol&&);
    Protocol& operator=(Protocol&&);

    void close();

    // Byte communicaiton!!
    void sendbyte(const uint8_t byte);
    uint8_t recvbyte();

    // Short communication!!
    uint16_t recvshort();
    void sendshort(const uint16_t num);


    // para mandar structs.. o similes
    void sendbytes(const void* msg, const unsigned int count);
    void recvbytes(void* buff, const unsigned int count);

    bool tryrecvbytes(void* buff, const unsigned int count);
    bool tryrecvbyte(uint8_t* out);


    // Signal action send.
    // Tries receive pickup order. If EOF then returns false.
    bool recvpickup();
    // Sends the pickup signal action
    void signalpickup();

    // Message communication fixed ... len is on host endiannes.. Conversion to
    // big endian happens at protocol.
    void sendmsg(const char* buff, const uint16_t len);
    void sendmsg(const std::string& message);

    // attemps read message of chars. Uses vector to store the len.
    std::vector<char> recvmsg();

    // Reads a vector and converts to string.
    std::string recvmsgstr();

    uint16_t recvmsg(char* buff,
                     const unsigned int max);  // attemps read msg, throws exception if len > max


    // Recibe el inicio de una notificacion. Retorna el tipo.
    uint8_t recvnotification();

    // Envia los bytes de identificacion para una notificacion, del tipo correspondiente.
    void notifyevent(uint8_t type);
};
#endif
