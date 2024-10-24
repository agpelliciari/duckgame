#include "./lobbyprotocol.h"

#include <iostream>
#include <utility>

#include "common/protocolerror.h"

LobbyProtocol::LobbyProtocol(LobbyContainer& _lobbies, ControlledPlayer& _player,
                             ServerProtocol& protocol):
        lobbies(_lobbies), player(_player), isanfitrion(false), match(NULL) {

    if (handleNewClient(protocol)) {
        throw ProtocolError("Protocol aborted in middle of handshake");
    }
}

void LobbyProtocol::doaction(ServerProtocol& protocol) {
    PlayerActionDTO action = protocol.recvaction();

    if (player.playercount() <= action.playerind) {
        std::cerr << "Invalid action from client!!\n";
        return;
    }

    action.playerind = player.getid(action.playerind);
    match->notifyAction(action);
}

bool LobbyProtocol::handleNewClient(ServerProtocol& protocol) {
    uint8_t playercount;
    if (!protocol.recvplayercount(&playercount)) {
        // std::cerr << "Player controller aborted" << std::endl;
        return true;  // Permitamos que se desconecte inicialmente si no se manda el count.
    }
    player.setplayercount(playercount);
    player.open();

    lobby_action info = protocol.recvlobbyaction();

    if (info.action == NEW_LOBBY) {
        isanfitrion = true;
        match = &lobbies.newLobby(&player);
        std::cerr << "New lobby id: " << (int)match->getID() << std::endl;
        return false;
    }
    isanfitrion = false;
    match = &lobbies.joinLobby(&player, info.attached_id);

    std::cerr << "Connected lobby info join lobby " << (int)match->getID() << std::endl;

    return false;
}

bool LobbyProtocol::start(ServerProtocol& protocol) {
    if (!isanfitrion) {
        return true;
    }

    if (protocol.recvsignalstart()) {
        std::cerr << "Started lobby id: " << (int)match->getID() << std::endl;
        lobbies.startLobby(*match);
        return true;
    }

    // std::cerr << "CANCELED LOBBY: " << (int)match->getID() << std::endl;
    return false;
}


LobbyProtocol::~LobbyProtocol() {
    player.disconnect();

    // El log a cerr podria ser innecesario. Pero sirve para hacer cosas mas descriptivas.
    std::cerr << ">closed Player " << player.getid(0) << std::endl;
    if (player.playercount() > 1) {
        std::cerr << ">closed Player " << player.getid(1) << std::endl;
    }

    if (isanfitrion) {
        lobbies.stopLobby(*match);
    }
}
