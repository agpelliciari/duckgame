#include "./play_state_recv.h"

#include <iostream>

#include "common/core/liberror.h"
#include "common/queue.h"

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
            } else if(stats.state == MatchStateType::LOADING){
                // Esta recargando el mapa!?!
                std::cout << "---->RELOADING MAP DATA!\n";
                context.map = MapData();
                protocol.recvmapdata(context.map);
                stats.state = PAUSADA; // Para que no se salga! del loop
                
            } else{
                listener.statsUpdated(stats);
            }
        }
        std::cerr << "finsihed.. play state received finish, close" << std::endl;
    } catch (const LibError&
                     error) {  // No deberia pasara realmente, antes pasaria en el controller.
        
        if(stats.isRunning()){
            if(protocol.isopen()){
                std::cerr << "canceling.. play state receiver error, was server disconnected?" << std::endl;
                stats.state = CANCELADA;
                listener.statsUpdated(stats);
            } else{
                std::cerr << "-->closed play receiver??" << std::endl;        
            }
        }
    } catch (const ClosedQueue& err) {
        std::cerr << "Game force close!" << std::endl;
        protocol.close();  // Si no esta cerrado
    }
}

PlayStateRecv::~PlayStateRecv() {
    stop();
    join();
}
