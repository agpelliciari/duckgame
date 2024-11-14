#include "./play_state_recv.h"

#include <iostream>

#include "common/core/liberror.h"

PlayStateRecv::PlayStateRecv(ClientProtocol& _protocol, EventListener& _listener,
                             GameContext& _context):
        protocol(_protocol), listener(_listener), context(_context) {}

void PlayStateRecv::run() {
    try {
        while (_keep_running) {
            // Capaz termino?
            // Por ahora solo recibe matchdtos..
            MatchDto state = protocol.recvstate();
            // Aplica transformaciones. A coordenadas
            for (PlayerDTO& player: state.players) {
                // inverti/escala
                // MAP_BLOCK_UNIT*
                player.pos.y = (player.pos.y + context.map.height);
                player.pos.x = (player.pos.x);

                // std::cerr << "-->player" << (int)player.id << " at " << player.pos.x << ","
                //      << player.pos.y << std::endl;
            }

            for (DynamicObjDTO& obj: state.objects) {
                // MAP_BLOCK_UNIT*
                obj.pos.y = (context.map.height - obj.pos.y * MAP_BLOCK_UNIT);  // Inverti!
                obj.pos.x = (obj.pos.x);
            }


            listener.matchUpdated(state);
        }
    } catch (const LibError&
                     error) {  // No deberia pasara realmente, antes pasaria en el controller.
        std::cerr << "game state receiver error " << error.what() << std::endl;
    }
}

PlayStateRecv::~PlayStateRecv() {
    stop();
    join();
}
