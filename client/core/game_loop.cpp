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

GameLoop::GameLoop(const char* host, const char* service): protocol(Socket(host, service)) {}
GameLoop::GameLoop(const char* service): GameLoop(NULL, service) {}

// Permitamos el mov desde uno existente para mayor flexibilidad?
GameLoop::GameLoop(Protocol&& prot): protocol(std::move(prot)) {}

LobbyClientSender GameLoop::initLobbyClient(GameContext& context) {
    return LobbyClientSender(protocol, context);
}
GameActionSender GameLoop::initGame(EventListener& listener) {
    return GameActionSender(protocol, listener);
}
GameLoop::~GameLoop() {}
