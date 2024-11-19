#include "./lobby_create_state.h"

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "./lobby_action_sender.h"
#include "common/core/liberror.h"
#include "common/protocolerror.h"

#define getErrorMsg(ind) ERRORS[(ind >= 8) ? 1 : ind]


LobbyCreateState::LobbyCreateState(Messenger& _messenger, GameContext& _context,
                                   LobbyListener& _listener):
        LobbyStateRecv(_messenger, _context, _listener) {}

void LobbyCreateState::createLobby() {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    start();
}

LobbyActionQueue& LobbyCreateState::getSender() { return sender; }

bool LobbyCreateState::checkcreatefail() {

    try {

        if (context.dualplay) {
            std::vector<std::string> maps;
            uint8_t id_lobby = protocol.sendCreateLobby(2,maps);

            context.second_player = protocol.recvIDDualPlayer(&context.first_player);
            context.id_lobby = id_lobby;

            context.players.reserve(context.max_player_count);
            context.addPlayer(context.first_player);
            context.addPlayer(context.second_player);
            
            // Para probar!
            maps.push_back("does not exist");
            
            listener.createdLobbyDual(id_lobby,maps);
        } else {
            std::vector<std::string> maps;
            uint8_t id_lobby = protocol.sendCreateLobby(1,maps);

            context.first_player = protocol.recvIDSinglePlayer();
            context.second_player = 0;
            context.id_lobby = id_lobby;
            
            context.players.reserve(context.max_player_count);
            context.addPlayer(context.first_player);

            // Para probar!
            maps.push_back("does not exist");

            listener.createdLobbySolo(id_lobby,maps);
        }
        return false;
    } catch (const LibError& error) {
        if (protocol.isopen()) {
            std::cerr << "Lobby create lib error:" << error.what() << std::endl;
            listener.failedCreate(CLIENT_CONN_ERROR);
        }
        return true;
    }
}
void LobbyCreateState::run() {
    if (checkcreatefail()) {
        return;
    }

    try {
        LobbyActionSender actionlisten(protocol, sender);
        actionlisten.begin();

        // Wait until start/cancel info.
        lobby_info info = listenUntilLobbyEnd();

        if (info.action == LobbyResponseType::STARTED_LOBBY) {
            setInitedMatch();
        } else {
            context.started = false;
            listener.canceledLobby(getErrorMsg(info.data));
        }
    } catch (const LibError& error) {
        if (protocol.isopen()) {
            std::cerr << "CreateLobby state recv error:" << error.what() << std::endl;
            listener.canceledLobby(CLIENT_CONN_ERROR);
        }
    }
}
