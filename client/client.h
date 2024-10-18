#ifndef LIB_Client_H
#define LIB_Client_H

#include <string>
#include <utility>

#include "common/protocol.h"
#include "common/socket.h"
#include "./clientprotocol.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class Client {
protected:
    ClientProtocol protocol;
    unsigned int inputnum();

public:
    // Los default sin pasar por socket/protocol.
    explicit Client(const char* host, const char* service): protocol(Socket(host, service)) {}
    explicit Client(const char* service): Client(NULL, service) {}

    // Permitamos el mov desde uno existente para mayor flexibilidad?
    explicit Client(Protocol&& prot): protocol(std::move(prot)) {}

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;


    // Se crea un loop escuchande el stdin acciones para ejecutar.
    void listenActions();
};

#endif
