#include "./lobby_client_sender.h"

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


LobbyClientSender::LobbyClientSender(ClientProtocol& _protocol, GameContext& _context,
                                     LobbyListener& _listener):
        protocol(_protocol),
        mode(NULL),
        context(_context),
        started_match(false),
        listener(_listener) {}


void LobbyClientSender::notifyStart() {
    std::unique_lock<std::mutex> lck(mtx);
    started_match = true;
    match_start.notify_all();
}

void LobbyClientSender::notifyCancel() {
    std::unique_lock<std::mutex> lck(mtx);
    started_match = false;
    match_start.notify_all();
}


void LobbyClientSender::cancel() {}
void LobbyClientSender::doaction(const lobby_action& action) {
    std::cout << "SEND ACTION? " << &action << std::endl;
}

void LobbyClientSender::handleJoin() {
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
    if (success.action == LobbyActionType::STARTED_LOBBY) {
        // std::cout << "Joined Lobby id " << (int)context.id_lobby
        //           << " INICIADA CON count: " << (int)success.attached_id << std::endl;
        context.started = true;
        context.cantidadjugadores = success.attached_id;

        listener.startedLobby();
    } else {
        std::cout << "Join Lobby id " << (int)context.id_lobby
                  << " FALLO CODE: " << (int)success.attached_id << std::endl;
        context.started = false;
        listener.canceledLobby();
    }
}

void LobbyClientSender::waitStart() {
    std::unique_lock<std::mutex> lck(mtx);
    match_start.wait(lck);
}
void LobbyClientSender::handleCreate() {
    uint8_t id_lobby = protocol.createLobby();

    if (context.dualplay) {
        context.second_player = protocol.setdualplay(&context.first_player);
        listener.createdLobbyDual(context);
    } else {
        context.first_player = protocol.setsingleplay();
        context.second_player = 0;
        listener.createdLobbySolo(context);
    }

    waitStart();
    if (started_match) {
        protocol.startlobby();
        lobby_info success;
        protocol.recvlobbyinfo(success);
        if (success.action == LobbyActionType::STARTED_LOBBY) {
            // std::cout << "Lobby id " << (int)id_lobby
            //           << " INICIADA CON count: " << (int)success.attached_id << std::endl;
            context.started = true;
            context.cantidadjugadores = success.attached_id;
            listener.startedLobby();
        } else {
            std::cout << "Lobby id " << (int)id_lobby << " FALLO EL EMPEZAR" << std::endl;
            context.started = false;
            listener.canceledLobby();
        }
    }
}

void LobbyClientSender::createLobby(bool dualplay) {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    context.dualplay = dualplay;
    mode = &LobbyClientSender::handleCreate;
    start();
}

void LobbyClientSender::joinLobby(bool dualplay, unsigned int idlobby) {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }

    context.dualplay = dualplay;

    context.id_lobby = idlobby;
    mode = &LobbyClientSender::handleJoin;
    start();
}


bool LobbyClientSender::isrunning() { return _is_alive; }
void LobbyClientSender::run() {
    (this->*mode)();  // exec lobby mode.
}

bool LobbyClientSender::endstate() {
    if (started_match) {
        return true;
    }
    notifyCancel();
    return false;
}

LobbyClientSender::~LobbyClientSender() {
    if (_keep_running) {
        stop();
        notifyCancel();
        join();
    }
}
