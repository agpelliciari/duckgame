#include "game_loop.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"

#define ASK_NAME "What is your name?"
#define ACTION_EXIT "Exit"
#define ACTION_PICKUP "Pickup"
#define ACTION_READ "Read"

// GameLoop::GameLoop(const char* host, const char* service): protocol(Socket(host, service)) {}
// GameLoop::GameLoop(const char* service): GameLoop(NULL, service) {}

GameLoop::GameLoop(): protocol() {}


void GameLoop::setHostnamePort(const char* host, const char* service) {
    std::cout << "Set hostname y port: " << host << " : " << service << std::endl;
    protocol.reset(new ClientProtocol(Socket(host, service)));
}


// Se podria usar los move constructors y que no... pero si al final hace lo mismo!!
void GameLoop::updateLobbySender(LobbyClientSender& sender) { sender.swapProtocol(protocol.get()); }

GameActionSender GameLoop::initGame(EventListener& listener) {
    return GameActionSender(*protocol.get(), listener);
}
GameLoop::~GameLoop() {}
