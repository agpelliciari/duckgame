#include "./base_lobby_state.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "common/errors.h"
#include "common/protocolerror.h"

const char* BaseLobbyState::ERRORS[] = {
        "Client connection error",     "Unknown server error", "Server closed the connection",
        "Match's host left the lobby", "Lobby was not found",  "Lobby was already started",
        "Lobby had not enough space"};

BaseLobbyState::BaseLobbyState(Messenger& _messenger, GameContext& _context,
                               LobbyListener& _listener):
        protocol(_messenger), context(_context), listener(_listener) {}


void BaseLobbyState::handleNotify(const lobby_info& info) {
    // Un map para esto... no vale la pena.
    if (info.action == PLAYER_NEW) {
        context.cantidadjugadores++;
        listener.playerJoinedLobby(info.data);
    } else if (info.action == PLAYER_LEFT) {
        context.cantidadjugadores--;
        listener.playerLeftLobby(info.data);
    }
}

void BaseLobbyState::listeninfo() {
    lobby_info info;
    try {
        protocol.recvlobbyinfo(info);

        while (info.action != LobbyResponseType::STARTED_LOBBY &&
               info.action != LobbyResponseType::GAME_ERROR) {

            handleNotify(info);
            protocol.recvlobbyinfo(info);
        }
    } catch (const LibError& error) {
        if (protocol.isopen()) {
            std::cerr << "Lobby state recv error:" << error.what() << std::endl;
            listener.canceledLobby(ERRORS[0]);
        }
        return;
    }

    if (info.action == LobbyResponseType::STARTED_LOBBY) {
        context.started = true;
        context.cantidadjugadores = info.data;
        listener.startedLobby();
    } else {
        std::cout << "Game error received " << (int)context.id_lobby
                  << " FALLO CODE: " << (int)info.data << std::endl;
        context.started = false;

        listener.canceledLobby(ERRORS[(info.data >= 7) ? 1 : info.data]);
    }
}

bool BaseLobbyState::endstate() {
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

BaseLobbyState::~BaseLobbyState() {
    if (_keep_running) {
        stop();
        if (!context.started) {
            protocol.close();
        }
        join();
    }
}
