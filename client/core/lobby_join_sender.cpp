#include "./lobby_join_sender.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "common/protocolerror.h"

LobbyJoinSender::LobbyJoinSender(ClientProtocol& _protocol, GameContext& _context,
                                 LobbyListener& _listener):
        protocol(_protocol), context(_context), started_match(false), listener(_listener) {}

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

    lobby_info success;
    protocol.recvlobbyinfo(success);
    if (success.action == LobbyResponseType::STARTED_LOBBY) {
        // std::cout << "Joined Lobby id " << (int)context.id_lobby
        //           << " INICIADA CON count: " << (int)success.data << std::endl;
        context.started = true;
        started_match = true;
        context.cantidadjugadores = success.data;

        // No hace falta por ahora. Ya que no hay ninguna configuracion posible.
        // protocol.sendready(); // Notifica que se cambio al modo juego. Podria ser antes.

        listener.startedLobby();

    } else {
        std::cout << "Join Lobby id " << (int)context.id_lobby
                  << " FALLO CODE: " << (int)success.data << std::endl;
        started_match = false;
        context.started = false;
        listener.canceledLobby();
    }
}

bool LobbyJoinSender::endstate() {
    if (started_match) {
        return true;
    }
    std::cout << "JOIN ENTERED END STATE?!" << std::endl;
    // stop();
    // protocol.close();
    // join();
    return false;
}

LobbyJoinSender::~LobbyJoinSender() {
    if (_keep_running) {
        stop();
        // protocol.close();
        // notifyCancel();
        join();
    }
}
