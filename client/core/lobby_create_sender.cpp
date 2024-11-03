#include "./lobby_create_sender.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "./lobby_action_listener.h"
#include "common/core/liberror.h"
#include "common/protocolerror.h"


LobbyCreateSender::LobbyCreateSender(Messenger& _messenger, GameContext& _context,
                                     LobbyListener& _listener):
        BaseLobbyState(_messenger, _context, _listener) {}

void LobbyCreateSender::createLobby() {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    start();
}

LobbyClientSender& LobbyCreateSender::getSender() { return sender; }


void LobbyCreateSender::run() {

    uint8_t id_lobby = protocol.createLobby();

    if (context.dualplay) {
        context.second_player = protocol.setdualplay(&context.first_player);
        context.id_lobby = id_lobby;

        listener.createdLobbyDual(id_lobby);
    } else {
        context.first_player = protocol.setsingleplay();
        context.second_player = 0;

        context.id_lobby = id_lobby;
        listener.createdLobbySolo(id_lobby);
    }

    LobbyActionListener actionlisten(protocol, sender);
    actionlisten.begin();

    // Open info receiver.
    listeninfo();

    /*
    if (started_match) {
        protocol.sendready();
        lobby_info success;
        protocol.recvlobbyinfo(success);
        if (success.action == LobbyResponseType::STARTED_LOBBY) {
            // std::cout << "Lobby id " << (int)id_lobby
            //           << " INICIADA CON count: " << (int)success.data << std::endl;
            context.started = true;
            context.cantidadjugadores = success.data;
            listener.startedLobby();
        } else {
            std::cout << "Lobby id " << (int)id_lobby << " FALLO EL EMPEZAR" << std::endl;
            context.started = false;
            listener.canceledLobby();
        }
    }
        */
}
