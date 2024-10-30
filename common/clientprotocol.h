#ifndef LIB_ClientProtocol_H
#define LIB_ClientProtocol_H

#define BUFF_LEN_CLIENT 128


#include <atomic>
#include <string>
#include <utility>

#include "common/core/protocol.h"
#include "common/dtos.h"

// Extension del protocolo base a usar.
class ClientProtocol {

protected:
    Protocol protocol;  // Composicion con el protocolo base para la conexion
    std::atomic<bool> isactive;

public:
    // El default a partir de la abstraccion de socket
    explicit ClientProtocol(Messenger* connection);
    explicit ClientProtocol(Socket& connection);
    explicit ClientProtocol(Socket&& connection);

    // Un client protocol, inicialmente cerrado.
    ClientProtocol();

    // Para mayor facilidad... el move del client protocol permite mas facil
    // reiniciar una conexion.
    ClientProtocol(ClientProtocol&&);
    ClientProtocol& operator=(ClientProtocol&&);

    // Asumamos por ahora que no se quiere permitir copias
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    void joinLobby(const uint8_t id_match);
    uint8_t createLobby();

    // Para setear playercount == 1 o == 2
    uint8_t setsingleplay();
    uint8_t setdualplay(uint8_t* player1);


    void startlobby();

    void sendaction(PlayerActionDTO& action);

    MatchDto recvstate();


    bool isopen();
    void close();
};

#endif
