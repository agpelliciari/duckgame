#include "./lobby_create_sender.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "common/protocolerror.h"

#define ASK_NAME "What is your name?"
#define ACTION_EXIT "Exit"
#define ACTION_PICKUP "Pickup"
#define ACTION_READ "Read"


LobbyCreateSender::LobbyCreateSender(ClientProtocol& _protocol, GameContext& _context,
                                     LobbyListener& _listener):
        protocol(_protocol), context(_context), started_match(false), listener(_listener) {}


void LobbyCreateSender::notifyStart() {
    std::unique_lock<std::mutex> lck(mtx);
    started_match = true;
    match_start.notify_all();
}

void LobbyCreateSender::notifyCancel() {
    std::unique_lock<std::mutex> lck(mtx);
    started_match = false;
    match_start.notify_all();
}

void LobbyCreateSender::doaction(const lobby_action& action) {
    std::cout << "SEND ACTION? " << &action << std::endl;
}

void LobbyCreateSender::waitStart() {
    std::unique_lock<std::mutex> lck(mtx);
    match_start.wait(lck);
}

void LobbyCreateSender::createLobby() {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    start();
}

bool LobbyCreateSender::isrunning() { return _is_alive; }

void LobbyCreateSender::run() {

    uint8_t id_lobby = protocol.createLobby();

    if (context.dualplay) {
        context.second_player = protocol.setdualplay(&context.first_player);
        context.id_lobby = id_lobby;

        listener.createdLobbyDual(context);
    } else {
        context.first_player = protocol.setsingleplay();
        context.second_player = 0;

        context.id_lobby = id_lobby;
        listener.createdLobbySolo(context);
    }

    // Open info receiver.
    waitStart();

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
}

bool LobbyCreateSender::endstate() {
    if (started_match) {
        return true;
    }
    notifyCancel();
    return false;
}

LobbyCreateSender::~LobbyCreateSender() {
    if (_keep_running) {
        stop();
        notifyCancel();
        join();
    }
}
