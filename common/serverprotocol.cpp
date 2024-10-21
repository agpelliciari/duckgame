#include "./serverprotocol.h"

#include <iostream>
#include <string>
#include <utility>

//#include "./gameerror.h"
#include "common/protocolerror.h"


ServerProtocol::ServerProtocol(Socket& messenger): protocol(messenger), isactive(true) {}
ServerProtocol::ServerProtocol(Messenger* messenger): protocol(messenger), isactive(true) {}
ServerProtocol::ServerProtocol(Protocol&& prot): protocol(std::move(prot)), isactive(true) {}


bool ServerProtocol::recvplayercount(uint8_t* count) { return protocol.tryrecvbyte(count); }

bool ServerProtocol::recvsignalstart() {
    uint8_t sign;
    if (protocol.tryrecvbyte(&sign)) {
        return (LobbyActionType)(sign) == LobbyActionType::STARTED_LOBBY;
    }

    return false;
}


lobby_action ServerProtocol::recvlobbyaction() {
    lobby_action out;
    protocol.recvbytes(&out, sizeof(out));
    return out;
}

PlayerActionDTO ServerProtocol::recvaction() {
    PlayerActionDTO action;
    if (!protocol.tryrecvbytes(&action, sizeof(action))) {
        isactive = false;
        throw ProtocolError("Did not receive action!");
    }
    return action;
}

void ServerProtocol::sendstate(const MatchDto&& state) {

    // Primero envia general info
    protocol.sendbytes(&state.info, sizeof(state.info));
    protocol.sendbyte(state.players.size());

    for (auto playerit = state.players.begin(); playerit != state.players.end();) {
        PlayerDTO player = *playerit;
        protocol.sendbytes(&player, sizeof(player));
        ++playerit;
    }
}


bool ServerProtocol::isopen() { return isactive.load(); }

void ServerProtocol::close() {
    if (isactive.exchange(false)) {
        protocol.close();
    }
}
