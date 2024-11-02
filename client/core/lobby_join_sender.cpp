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

    lobby_info infojoin = protocol.joinLobby(context.id_lobby);
    if (infojoin.action != JOINED_LOBBY) {
        std::cerr << "Failed joined error code: " << (int)infojoin.data << std::endl;
        listener.failedJoin();
        return;
    }

    if (context.dualplay) {
        // std::cerr << "lobby id to join: " << (int)context.id_lobby <<" DUAL"<< std::endl;
        context.second_player = protocol.setdualplay(&context.first_player);

        context.cantidadjugadores = infojoin.data + 2;
        listener.joinedLobbyDual(context);
    } else {
        // std::cerr << "lobby id to join: " << (int)context.id_lobby <<" SINGLE"<< std::endl;
        context.first_player = protocol.setsingleplay();
        context.second_player = 0;

        context.cantidadjugadores = infojoin.data + 1;
        listener.joinedLobbySolo(context);
    }

    listeninfo();
}
