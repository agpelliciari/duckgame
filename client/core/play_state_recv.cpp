#include "./play_state_recv.h"

#include <iostream>

#include "common/core/liberror.h"

PlayStateRecv::PlayStateRecv(ClientProtocol& _protocol, EventListener& _listener,
                             GameContext& _context):
        protocol(_protocol), listener(_listener), context(_context) {}

void PlayStateRecv::run() {
    MatchStatsInfo stats;
    stats.state = INICIADA;
    try {
        MatchDto state;

        while (_keep_running && stats.isRunning()) {

            // Actualiza ambas cosas
            // True si esta en un round
            // False si pausa/termino.
            if (protocol.recvstate(stats, state)) {
                // No es ideal pero he aqui.
                for(PlayerDTO& player: state.players){
                     player.pos.x-= 3; // Para centrar. Ya que 16 mide un bloque.
                }
                
                listener.matchUpdated(state);
            } else {
                // Chequea si finisheo?!
                listener.statsUpdated(stats);
            }
        }
    } catch (const LibError&
                     error) {  // No deberia pasara realmente, antes pasaria en el controller.
        
        if(stats.isRunning()){
            std::cerr << "canceling.. play state receiver error, was server disconnected?" << std::endl;
            stats.state = CANCELADA;
            listener.statsUpdated(stats);
        }
        
        
    }
}

PlayStateRecv::~PlayStateRecv() {
    stop();
    join();
}
