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

void ClientProtocol::joinLobby(const uint8_t id_match) {
    uint8_t info[2] = {LobbyActionType::JOIN_LOBBY, id_match};
    protocol.sendbytes(&info, 2);
}
uint8_t ClientProtocol::createLobby() {
    protocol.sendbyte(LobbyActionType::CREATE_LOBBY);
    return protocol.recvbyte();
}

uint8_t ClientProtocol::setsingleplay() {
    protocol.sendbyte(1);        // Send del playercount == 1
    return protocol.recvbyte();  // id player 1
}

uint8_t ClientProtocol::setdualplay(uint8_t* player1) {

    protocol.sendbyte(2);  // Send del playercount == 2
    *player1 = protocol.recvbyte();

    return protocol.recvbyte();
}


void ClientProtocol::startlobby() { protocol.sendbyte(LobbyActionType::STARTED_LOBBY); }

MatchDto ClientProtocol::recvstate() {
    // Primero recibi info general
    match_info_dto out;
    protocol.recvbytes(&out, sizeof(out));

    MatchDto res = MatchDto(out);

    int playercount = (int)protocol.recvbyte();

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
