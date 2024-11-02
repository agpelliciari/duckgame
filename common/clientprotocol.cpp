#include "./clientprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "common/dtos.h"

ClientProtocol::ClientProtocol(): protocol() {}
ClientProtocol::ClientProtocol(Messenger* conn): protocol(conn) {}
ClientProtocol::ClientProtocol(Socket& conn): protocol(conn) {}
ClientProtocol::ClientProtocol(Socket&& conn): protocol(conn) {}

ClientProtocol::ClientProtocol(ClientProtocol&& other): protocol(std::move(other.protocol)) {}

ClientProtocol& ClientProtocol::operator=(ClientProtocol&& other) {
    if (this == &other) {
        return *this;
    }

    protocol = std::move(other.protocol);
    return *this;
}

void ClientProtocol::recvlobbyinfo(lobby_info& out) {
    // Podria tirar cast error.
    out.action = (LobbyResponseType)protocol.recvbyte();
    out.data = protocol.recvbyte();
    // throw ProtocolError("Invalid lobby info action!");
}


void ClientProtocol::sendaction(PlayerActionDTO& action) {
    // std::cout << "Sending action from: " << (int)action.playerind << "= " << (int)action.type <<
    // std::endl;
    protocol.sendbytes(&action, sizeof(action));
}

bool ClientProtocol::joinLobby(const uint8_t id_match) {
    uint8_t info[2] = {LobbyActionType::JOIN_LOBBY, id_match};
    protocol.sendbytes(&info, 2);

    // Recibir true si fallo, false si fue exito.
    return protocol.recvbyte() != (LobbyActionType::JOIN_LOBBY);
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


void ClientProtocol::sendlobbyaction(const lobby_action&& action) {
    protocol.sendbyte(action.type);
}

MatchDto ClientProtocol::recvstate() {
    // Primero recibi info general
    match_info_dto out;
    protocol.recvbytes(&out, sizeof(out));

    MatchDto res = MatchDto(out);
    // std::cerr << "-----GOT UPDATE\n" << res.parse() << std::endl;

    int playercount = (int)protocol.recvbyte();

    while (playercount > 0) {
        PlayerDTO player;

        protocol.recvbytes(&player, sizeof(player));

        // std::cout << "EL PLAYER "<< player.id<< " RECV EN STATE: " << (int)player.move_action <<
        // std::endl;

        res.players.push_back(player);
        playercount--;
    }

    /*
    for (auto playerit = state.players.begin(); playerit != state.players.end();) {
        PlayerDTO player = *playerit;
        std::cerr << "-->" << (int)player.id << " at " << player.coord_x << ","
                  << player.coord_y << std::endl;
        ++playerit;
    }
    */
    return res;
}

// Manejo de si esta abierto o no.
bool ClientProtocol::isopen() { return protocol.isactive(); }

void ClientProtocol::close() { protocol.close(); }
