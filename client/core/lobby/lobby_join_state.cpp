#include "./lobby_join_state.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "common/protocolerror.h"

#define getErrorMsg(ind) ERRORS[(ind >= 8) ? 1 : ind]


LobbyJoinState::LobbyJoinState(Messenger& _messenger, GameContext& _context,
                               LobbyListener& _listener):
        LobbyStateRecv(_messenger, _context, _listener) {}

void LobbyJoinState::joinLobby() {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    start();
}

bool LobbyJoinState::isrunning() { return _is_alive; }

bool LobbyJoinState::tryJoinLobbyFail() {
    try {
        if (context.dualplay) {
            lobby_info infojoin = protocol.sendJoinLobby(context.id_lobby, context.players, 2);
            if (infojoin.action != JOINED_LOBBY) {
                std::cerr << "Failed join dual code: " << (int)infojoin.data << std::endl;
                listener.failedJoin(getErrorMsg(infojoin.data));
                return true;
            }

            context.second_player = protocol.recvIDDualPlayer(&context.first_player);

            //context.cantidadjugadores = infojoin.data;  // + 2;
            listener.joinedLobbyDual(context);
            return false;
        }

        lobby_info infojoin = protocol.sendJoinLobby(context.id_lobby, context.players, 1);
        if (infojoin.action != JOINED_LOBBY) {
            std::cerr << "Failed join single error code: " << (int)infojoin.data << std::endl;
            listener.failedJoin(getErrorMsg(infojoin.data));
            return true;
        }

        context.first_player = protocol.recvIDSinglePlayer();
        context.second_player = 0;

        //context.cantidadjugadores = infojoin.data;  // + 1;
        listener.joinedLobbySolo(context);

        return false;
    } catch (const LibError& error) {
        if (protocol.isopen()) {
            std::cerr << "Lobby join lib error:" << error.what() << std::endl;
            listener.failedJoin(CLIENT_CONN_ERROR);
        }
        return true;
    }
}


void LobbyJoinState::run() {
    if (tryJoinLobbyFail()) {
        return;
    }

    try {
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
            std::cerr << "JoinLobby state recv error:" << error.what() << std::endl;
            listener.canceledLobby(CLIENT_CONN_ERROR);
        }
    }
}
