#include "./playerprotocol.h"

#include <iostream>
#include <string>
#include <utility>

#include "./gameerror.h"
#include "common/event.h"


PlayerProtocol::PlayerProtocol(Socket&& skt): protocol(skt), isactive(true) {}

bool PlayerProtocol::recvplayercount(uint8_t* count) { return protocol.tryrecvbyte(count); }

bool PlayerProtocol::recvsignalstart() {
    uint8_t sign;
    if (protocol.tryrecvbyte(&sign)) {
        return (LobbyActionType)(sign) == LobbyActionType::STARTED_LOBBY;
    }

    return false;
}


lobby_action PlayerProtocol::recvlobbyaction() {
    lobby_action out;
    protocol.recvbytes(&out, sizeof(out));
    return out;
}

PlayerActionDTO PlayerProtocol::recvaction() {
    PlayerActionDTO action;
    if (!protocol.tryrecvbytes(&action, sizeof(action))) {
        isactive = false;
        throw GameError("Did not receive action!");
    }
    return action;
}

void PlayerProtocol::sendstate(const MatchDto&& state) {

    // Primero envia general info
    protocol.sendbytes(&state.info, sizeof(state.info));

    // Despues si es necesario envia los patos y asi.
}


bool PlayerProtocol::isopen() { return isactive.load(); }

void PlayerProtocol::close() {
    if (isactive.exchange(false)) {
        protocol.close();
    }
}
