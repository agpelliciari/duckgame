#include "./play_state_recv.h"

#include <iostream>

#include "common/core/liberror.h"

PlayStateRecv::PlayStateRecv(ClientProtocol& _protocol, EventListener& _listener,
                             GameContext& _context):
        protocol(_protocol), listener(_listener), context(_context) {}

void PlayStateRecv::run() {
    try {
        MatchDto state;
        MatchStatsInfo stats;

        while (_keep_running) {

            // Actualiza ambas cosas
            // True si esta en un round
            // False si pausa/termino.
            if (protocol.recvstate(stats, state)) {
                for (PlayerDTO& player: state.players) {

                    // std::cerr << "-->player" << (int)player.id << " at " << player.pos.x << ","
                    //       << player.pos.y << std::endl;

                    // inverti/escala
                    // MAP_BLOCK_UNIT* // la pos.y es negativa! por alguna razon. de logica del
                    // server
                    player.pos.y = (player.pos.y + context.map.height);
                    player.pos.x = (player.pos.x);
                }

                for (DynamicObjDTO& obj: state.objects) {
                    // std::cerr << "-->obj" << (int)obj.type << " at " << obj.pos.x << ","
                    //       << obj.pos.y << std::endl;

                    // MAP_BLOCK_UNIT*
                    if (obj.type == TypeDynamicObject::PROJECTILE) {
                        obj.pos.y = (context.map.height - obj.pos.y);  // Inverti!
                        continue;
                    }

                    obj.pos.y = (context.map.height - obj.pos.y * MAP_BLOCK_UNIT);  // Inverti!
                    obj.pos.x = (obj.pos.x);
                }
                listener.matchUpdated(state);
            } else {

                // Chequea si finisheo?!
                listener.statsUpdated(stats);
            }
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
