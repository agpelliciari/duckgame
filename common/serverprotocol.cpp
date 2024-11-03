#include "./serverprotocol.h"

#include <iostream>
#include <string>
#include <utility>

//#include "./gameerror.h"
#include "common/protocolerror.h"


ServerProtocol::ServerProtocol(Socket& messenger): protocol(messenger) {}
ServerProtocol::ServerProtocol(Messenger* messenger): protocol(messenger) {}
ServerProtocol::ServerProtocol(Protocol&& prot): protocol(std::move(prot)) {}

uint8_t ServerProtocol::recvplayercount() { return protocol.recvbyte(); }


LobbyActionType ServerProtocol::recvlobbyaction() {
    uint8_t sign;
    if (protocol.tryrecvbyte(&sign)) {
        return (LobbyActionType)sign;  // Podria fallar el casteo? la verificacion es posterior.
    }

    throw ProtocolError("Did not receive a lobby action");
}

/*
bool ServerProtocol::recvsignalstart() {
    uint8_t sign;
    return protocol.tryrecvbyte(&sign) && sign == ((uint8_t)LobbyActionType::STARTED_LOBBY);
}

*/

void ServerProtocol::notifyaction(const LobbyResponseType response) { protocol.sendbyte(response); }

void ServerProtocol::notifyinfo(const LobbyResponseType response, const uint8_t data) {
    uint8_t bytes[2] = {response, data};
    protocol.sendbytes(&bytes, 2);
}
void ServerProtocol::notifyevent(const lobby_info& info) {
    uint8_t bytes[2] = {info.action, info.data};
    protocol.sendbytes(&bytes, 2);
}

uint8_t ServerProtocol::recvlobbyid() { return protocol.recvbyte(); }

LobbyActionType ServerProtocol::recvresolveinfo() {
    uint8_t sign;
    if (!protocol.tryrecvbyte(&sign)) {
        throw ProtocolError("Did not receive lobby resolve info.");
    }
    if (LobbyActionType::CREATE_LOBBY == sign) {
        return CREATE_LOBBY;
    }

    if (LobbyActionType::JOIN_LOBBY == sign) {
        return JOIN_LOBBY;
    }

    throw ProtocolError("Invalid lobby resolve action!");
}

void ServerProtocol::notifyid(uint8_t id) { protocol.sendbyte(id); }


PlayerActionDTO ServerProtocol::recvaction() {
    PlayerActionDTO action;
    if (!protocol.tryrecvbytes(&action, sizeof(action))) {
        isactive = false;
        throw ProtocolError("Did not receive action!");
    }

    // std::cout << "Receiving action from: " << (int)action.playerind << "= " << (int)action.type
    //<< std::endl;

    return action;
}
void ServerProtocol::sendstate(const MatchDto&& state) { sendstate(state); }

void ServerProtocol::sendstate(const MatchDto& state) {

    // Primero envia general info
    protocol.sendbytes(&state.info, sizeof(state.info));
    protocol.sendbyte(state.players.size());

    for (auto playerit = state.players.begin(); playerit != state.players.end();) {
        PlayerDTO player = *playerit;

        // std::cout << "EL PLAYER "<< player.id<< " SENDED ESTA EN STATE: " <<
        // (int)player.move_action << std::endl;
        protocol.sendbytes(&player, sizeof(player));
        ++playerit;
    }
}


bool ServerProtocol::isopen() { return protocol.isactive(); }

void ServerProtocol::close() { protocol.close(); }
