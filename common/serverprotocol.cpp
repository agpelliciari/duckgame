#include "./serverprotocol.h"

#include <iostream>
#include <string>
#include <utility>

//#include "./gameerror.h"
#include "common/protocolerror.h"

ServerProtocol::ServerProtocol(Socket& messenger): Protocol(messenger) {}
ServerProtocol::ServerProtocol(Messenger* messenger): Protocol(messenger) {}
ServerProtocol::ServerProtocol(Protocol&& prot): Protocol(std::move(prot)) {}

uint8_t ServerProtocol::recvplayercount() { return this->recvbyte(); }

LobbyActionType ServerProtocol::recvlobbyaction() {
    uint8_t sign;
    if (this->tryrecvbyte(&sign)) {
        return (LobbyActionType)sign;  // Podria fallar el casteo? la verificacion es posterior.
    }

    throw ProtocolError("Did not receive a lobby action");
}

void ServerProtocol::notifyaction(const LobbyResponseType response) { this->sendbyte(response); }

void ServerProtocol::notifyinfo(const LobbyResponseType response, const uint8_t data) {
    uint8_t bytes[2] = {response, data};
    this->sendbytes(&bytes, 2);
}
void ServerProtocol::notifyevent(const lobby_info& info) {
    uint8_t bytes[2] = {info.action, info.data};
    this->sendbytes(&bytes, 2);
}

uint8_t ServerProtocol::recvlobbyid() { return this->recvbyte(); }

LobbyActionType ServerProtocol::recvresolveinfo() {
    uint8_t sign;
    if (!this->tryrecvbyte(&sign)) {
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

void ServerProtocol::notifyid(uint8_t id) { this->sendbyte(id); }


PlayerActionDTO ServerProtocol::recvaction() {
    PlayerActionDTO action;
    if (!this->tryrecvbytes(&action, sizeof(action))) {
        active = false;
        throw ProtocolError("Did not receive action!");
    }

    // std::cout << "Receiving action from: " << (int)action.playerind << "= " << (int)action.type
    //<< std::endl;

    return action;
}
void ServerProtocol::sendstate(const MatchDto&& state) { sendstate(state); }

void ServerProtocol::sendstate(const MatchDto& state) {

    // Primero envia general info
    this->sendbytes(&state.info, sizeof(state.info));
    this->sendbyte(state.players.size());

    for (const PlayerDTO& player: state.players) {
        sendplayer(player);
    }
}

// Para mayor flexibilidad.. por ahora.
void ServerProtocol::sendplayer(const PlayerDTO& player) {
    // std::cout << "EL PLAYER "<< player.id<< " SENDED ESTA EN STATE: " <<
    // (int)player.move_action << std::endl;
    this->sendbytes(&player, sizeof(player));
}


// bool ServerProtocol::isopen() { return this->isactive(); }

// void ServerProtocol::close() { this->close(); }
