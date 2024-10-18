#ifndef LIB_ClientProtocol_H
#define LIB_ClientProtocol_H

#define BUFF_LEN_CLIENT 128
#include <string>
#include <utility>

#include "../common_src/event.h"
#include "../common_src/protocol.h"

// Extension del protocolo base a usar.
class ClientProtocol {

protected:
    Protocol protocol;  // Composicion con el protocolo base para la conexion

public:
    // El default a partir de socket, te ahorras el move del protocol en si.
    explicit ClientProtocol(Socket connection);

    // Permitamos el mov para mayor flexibilidad
    explicit ClientProtocol(Protocol&& prot): protocol(std::move(prot)) {}

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = delete;
    ClientProtocol& operator=(ClientProtocol&&) = delete;

    void pickup(const std::string& name, const uint8_t box);
    Event recvevent();
};

#endif
