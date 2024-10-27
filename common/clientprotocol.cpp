#include "./clientprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "common/dtos.h"

ClientProtocol::ClientProtocol(Messenger* conn): protocol(conn) {}
ClientProtocol::ClientProtocol(Socket& conn): protocol(conn) {}
ClientProtocol::ClientProtocol(Socket&& conn): protocol(conn) {}

ClientProtocol::ClientProtocol(Protocol&& prot): protocol(std::move(prot)) {}

void ClientProtocol::sendaction(PlayerActionDTO& action) {
    protocol.sendbytes(&action, sizeof(action));
}

void ClientProtocol::joinLobby(const uint8_t playercount, const uint8_t id_match) {

    protocol.sendbyte(playercount);  // Primero se envia el player count.

    // Despues info de la lobby.
    lobby_action info = {LobbyActionType::JOIN_LOBBY, id_match};
    protocol.sendbytes(&info, sizeof(info));
}
void ClientProtocol::createLobby(const uint8_t playercount) {
    protocol.sendbyte(playercount);

    // Default 0 como mapa... que es reservado para que sea al azar.
    lobby_action info = {LobbyActionType::NEW_LOBBY, 0};
    protocol.sendbytes(&info, sizeof(info));
}

void ClientProtocol::startlobby() { protocol.sendbyte(LobbyActionType::STARTED_LOBBY); }


MatchDto ClientProtocol::recvstate() {
    // Primero recibi info general
    match_info_dto out;
    protocol.recvbytes(&out, sizeof(out));

    MatchDto res = MatchDto(out);

    int playercount = (int)protocol.recvbyte();
    // std::cout << "----> RECV PLAYER COUNT" << playercount << std::endl;

    while (playercount > 0) {
        PlayerDTO player;

        protocol.recvbytes(&player, sizeof(player));

        // std::cout << "RECV PLAYER: " << player.id << "at:" << player.coord_x << ","
        //           << player.coord_y << std::endl;

        res.players.push_back(player);
        playercount--;
    }
    return res;
}

void ClientProtocol::close() { protocol.close(); }
