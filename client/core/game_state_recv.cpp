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
            std::cerr << "-----GOT UPDATE\n" << state.parse() << std::endl;
            for (auto playerit = state.players.begin(); playerit != state.players.end();) {
                PlayerDTO player = *playerit;
                std::cerr << "-->" << (int)player.id << " at " << player.coord_x << ","
                          << player.coord_y << std::endl;
                ++playerit;
            }

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
