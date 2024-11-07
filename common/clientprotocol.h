#ifndef LIB_ClientProtocol_H
#define LIB_ClientProtocol_H

#define BUFF_LEN_CLIENT 128


#include <atomic>
#include <string>
#include <utility>
#include <vector>

#include "common/core/protocol.h"
#include "common/dtosgame.h"
#include "common/dtoslobby.h"
#include "common/dtosmap.h"

// Extension del protocolo base a usar.
class ClientProtocol {

protected:
    Protocol protocol;  // Composicion con el protocolo base para la conexion
public:
    // El default a partir de la abstraccion de socket
    explicit ClientProtocol(Messenger& connection);

    // Para mayor facilidad... el move del client protocol permite mas facil
    // reiniciar una conexion.
    ClientProtocol(ClientProtocol&&) = delete;
    ClientProtocol& operator=(ClientProtocol&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    lobby_info joinLobby(const uint8_t id_match);
    uint8_t createLobby();

    // Para setear playercount == 1 o == 2
    uint8_t setsingleplay();
    uint8_t setdualplay(uint8_t* player1);

    void recvlobbyinfo(lobby_info& out);

    void sendlobbyaction(const lobby_action&& action);

    void sendaction(PlayerActionDTO& action);

    MatchDto recvstate();
    struct MapPoint recvmap(uint8_t* background, std::vector<BlockDTO>& out);

    bool isopen();
    void close();
};

#endif
