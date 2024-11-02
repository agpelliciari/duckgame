#include "./lobby_join_sender.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "common/protocolerror.h"

LobbyJoinSender::LobbyJoinSender(ClientProtocol& _protocol, GameContext& _context,
                                 LobbyListener& _listener):
        BaseLobbyState(_protocol, _context, _listener) {}

void LobbyJoinSender::joinLobby() {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    start();
}

bool LobbyJoinSender::isrunning() { return _is_alive; }

void LobbyJoinSender::run() {
    // std::cerr << "lobby id to join: " << (int)context.id_lobby << std::endl;
    if (protocol.joinLobby(context.id_lobby)) {
        listener.failedJoin();
        return;
    }

    if (context.dualplay) {
        context.second_player = protocol.setdualplay(&context.first_player);
        listener.joinedLobbyDual(context);
    } else {
        context.first_player = protocol.setsingleplay();
        context.second_player = 0;
        listener.joinedLobbySolo(context);
    }

    listeninfo();
}
