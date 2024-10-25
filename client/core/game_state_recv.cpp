#include "./game_state_recv.h"

#include <iostream>

#include "common/core/liberror.h"

GameStateRecv::GameStateRecv(ClientProtocol& _protocol, EventListener& _listener):
        protocol(_protocol), listener(_listener) {}

void GameStateRecv::run() {
    try {
        while (_keep_running) {
            // Capaz termino?
            // Por ahora solo recibe matchdtos..
            MatchDto state = protocol.recvstate();

            listener.matchUpdated(state);
        }
    } catch (const LibError&
                     error) {  // No deberia pasara realmente, antes pasaria en el controller.
        std::cerr << "game state receiver error " << error.what() << std::endl;
    }
}

GameStateRecv::~GameStateRecv() {
    stop();
    join();
}
