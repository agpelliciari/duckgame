#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "./lobby_join_sender.h"
#include "common/core/liberror.h"
#include "common/protocolerror.h"

LobbyJoinSender::LobbyJoinSender(Messenger& _messenger, GameContext& _context,
                                 LobbyListener& _listener):
        BaseLobbyState(_messenger, _context, _listener) {}

void LobbyJoinSender::joinLobby() {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    start();
}

bool LobbyJoinSender::isrunning() { return _is_alive; }

void LobbyJoinSender::run() {
    try {
        lobby_info infojoin = protocol.joinLobby(context.id_lobby);
        if (infojoin.action != JOINED_LOBBY) {
            std::cerr << "Failed joined error code: " << (int)infojoin.data << std::endl;
            listener.failedJoin(ERRORS[infojoin.data]);
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
    } catch (const LibError& error) {
        if (protocol.isopen()) {
            std::cerr << "Lobby join lib error:" << error.what() << std::endl;
            listener.failedJoin(ERRORS[0]);
        }
        return;
    }


    listeninfo();
}
