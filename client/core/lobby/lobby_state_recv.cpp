#include "./lobby_state_recv.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "common/errors.h"
#include "common/protocolerror.h"

const char LobbyStateRecv::CLIENT_CONN_ERROR[] = "Client connection error";
const char* LobbyStateRecv::ERRORS[] = {
        "Unknown client error",        "Unknown server error", "Server closed the connection",
        "Match's host left the lobby", "Lobby was not found",  "Lobby was already started",
        "Lobby had not enough space"};

#define getErrorMsg(ind) ERRORS[(ind >= 7) ? 1 : ind]


LobbyStateRecv::LobbyStateRecv(Messenger& _messenger, GameContext& _context,
                               LobbyListener& _listener):
        protocol(_messenger), context(_context), listener(_listener) {}


void LobbyStateRecv::handleNotify(const lobby_info& info) {
    // Un map para esto... no vale la pena.
    if (info.action == PLAYER_NEW) {
        context.cantidadjugadores++;
        listener.playerJoinedLobby(info.data);
    } else if (info.action == PLAYER_LEFT) {
        context.cantidadjugadores--;
        listener.playerLeftLobby(info.data);
    }
}


void LobbyStateRecv::setInitedMatch(int totalplayers) {
    // Receive map data.
    protocol.recvmapdata(context.map, MAP_BLOCK_UNIT);

    context.started = true;
    context.cantidadjugadores = totalplayers;

    listener.startedLobby();
}

lobby_info LobbyStateRecv::listenUntilLobbyEnd() {
    lobby_info info;
    protocol.recvlobbyinfo(info);

    while (info.action != LobbyResponseType::STARTED_LOBBY &&
           info.action != LobbyResponseType::GAME_ERROR) {

        handleNotify(info);
        protocol.recvlobbyinfo(info);
    }
    return info;
}

bool LobbyStateRecv::endstate() {
    if (_keep_running) {
        stop();
        if (!context.started) {
            std::cout << "JOIN NOT HAPPENED SO CLOSE SOCKET!?!" << std::endl;
            protocol.close();
        }
        join();
    }
    return context.started;
}

LobbyStateRecv::~LobbyStateRecv() {
    if (_keep_running) {
        stop();
        if (!context.started) {
            protocol.close();
        }
        join();
    }
}
