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


LobbyClientSender::LobbyClientSender(ClientProtocol& _protocol, GameContext& _context):
        protocol(&_protocol), mode(NULL), context(_context), playercount(0) {}

LobbyClientSender::LobbyClientSender(LobbyClientSender&& other):
        protocol(other.protocol), mode(NULL), context(other.context), playercount(0) {
    other.protocol = NULL;
    std::cout << "MOVED CLIENT SENDER OWN " << protocol << std::endl;
}
LobbyClientSender& LobbyClientSender::operator=(LobbyClientSender&& other) {
    if (protocol == other.protocol) {
        return *this;
    }

    this->protocol = other.protocol;
    this->mode = other.mode;
    this->playercount = other.playercount;
    this->context = other.context;
    other.protocol = NULL;

    return *this;
}

void LobbyClientSender::cancel() {}
void LobbyClientSender::doaction(const lobby_action& action) {
    std::cout << "SEND ACTION? " << &action << std::endl;
}

void LobbyClientSender::handleJoin() {
    std::cerr << "lobby id to join: " << (int)context.id_lobby << std::endl;
    protocol->joinLobby(playercount, context.id_lobby);
}

void LobbyClientSender::handleCreate() {
    protocol->createLobby(playercount);

    std::cerr << "press enter to start the match!" << std::endl;

    std::string action;
    if (!(std::cin >> action)) {  // Could not read if new lobby.
        throw ProtocolError("Did not read match start!!");
    }

    protocol->startlobby();
}

void LobbyClientSender::createLobby(uint8_t playercount) {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    this->playercount = playercount;
    mode = &LobbyClientSender::handleCreate;
    start();
}

void LobbyClientSender::joinLobby(uint8_t playercount, unsigned int idlobby) {
    if (_is_alive) {  // already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }

    this->playercount = playercount;

    context.id_lobby = idlobby;
    mode = &LobbyClientSender::handleJoin;
    start();
}


bool LobbyClientSender::isrunning() { return _is_alive; }
void LobbyClientSender::run() {
    (this->*mode)();  // exec lobby mode.
}


int LobbyClientSender::getcount() {
    std::cout << ASK_NAME << std::endl;

    std::string name;
    if (!(std::getline(std::cin, name, '\n'))) {  // Could not read name.
        throw LibError(1, "Could not read player name");
    }

    std::string name2;

    std::cerr << ASK_NAME << " segundo player" << std::endl;
    if (!(std::getline(std::cin, name2, '\n'))) {  // Could not read name.
        throw LibError(1, "Could not read second player name");
    }

    if (name2.size() > 0) {
        std::cerr << "2 players: " << name << " " << name2 << std::endl;
        return 2;
    }
    std::cerr << "1 player: " << name << std::endl;
    return 1;
}


LobbyClientSender::~LobbyClientSender() {
    if (_keep_running) {
        stop();
        join();
    }
}
