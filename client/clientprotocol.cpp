#include "client/clientprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "common/dtos.h"
#include "common/liberror.h"

ClientProtocol::ClientProtocol(Socket skt): protocol(skt) {}

void ClientProtocol::pickup(const uint8_t indplayer, const uint8_t box) {

    uint8_t tosend = box - 1;
    // se le resta 1 a la box.
    PlayerActionDTO action = {PlayerActionType::PICK_UP, indplayer, tosend};
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

    // Despues lee la cantidad necesaria de cosas.

    return MatchDto(out);
}
