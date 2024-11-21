#include "./controlnotifier.h"

#include <iostream>

#include "common/core/liberror.h"

ControlNotifier::ControlNotifier(Match& _match,LobbyContainer& _lobbies, ControlledPlayer& _player,
                                 ServerProtocol& _protocol):
        match(_match),lobbies(_lobbies), player(_player), protocol(_protocol) {}

bool ControlNotifier::runLobby() {
    std::cerr << "#lobby notify for " << player.toString() << " at match " << (int)match.getID()
              << " start!" << std::endl;
    try {
        lobby_info info = player.popinfo();

        // El start se envia con un close asi que solo si ocurre un error
        while (_keep_running) {
            std::cerr << "match " << (int)match.getID() << " info to " << player.toString() << "? "
                      << (int)info.action << ", num: " << (int)info.data << std::endl;

            protocol.notifyevent(info);

            if (info.action == LobbyResponseType::GAME_ERROR) {
                // std::cout << "----> IF NOTIFY ERROR FROM HERE THEN CUSTOM/LOGIC ERROR??\n";
                protocol.close();
                return true;  // Si fue un error el notificado entonces sali.
            }

            info = player.popinfo();
        }

        std::cerr << "Closed notifier before match start, why?" << std::endl;
        protocol.notifyinfo(LobbyResponseType::GAME_ERROR, LobbyErrorType::UNKNOWN);
        protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
        return false;
    } catch (const ClosedQueue& error) {
    
        if (protocol.isactive()) {
            if(match.isrunning()){
                
                protocol.notifyinfo(LobbyResponseType::STARTED_LOBBY, match.playercount());
                protocol.sendmapinfo(match.getMap());
                return true;
            }
            std::cout << "Notifier lobby recv cancel match?\n";
            protocol.close();
            // Fue cancelada la partida?
            return false;
        }        
        return false;
    }
}


bool ControlNotifier::runPostGame(MatchStateType state) {
    if (state == TERMINADA || state == CANCELADA ) {
        protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
        return false;      // Se cerro el game
    }

    if (state == INICIADA) {
        //std::cerr << "Notifier go right back already started!! to " << (int)match.getID() << " " << player.toString()<<std::endl;
        return true;
    }
    try {
        player.waitgamemode();
        std::cerr << "Despausada " << (int)match.getID() << " info to " << player.toString() << std::endl;            
        protocol.sendstats(player.getStats());
        return true;
    } catch (const ClosedQueue& error) {        
        std::cerr << "At Pause Cancelada " << (int)match.getID() << " info to " << player.toString() << std::endl;
        protocol.close();  // Closed server while in pause?
        return false;
    }
}
MatchStateType ControlNotifier::runGame() {

    //std::cerr << player.toString() << " went to play mode!\n";
    //std::cerr << "#game notify for " << player.toString() << " at match " << (int)match.getID()
    //          << " start!" << std::endl;
    try {
        while (_keep_running) {
            protocol.sendstate(player.popstate());
        }

        return CANCELADA;
    } catch (const ClosedQueue& error) {
        const MatchStatsInfo& stats = player.getStats();
        if(stats.state != CANCELADA){ // Si fue cancelada el close es suficiente
            //std::cout << player.toString() << " exited game mode...:: " << stats.parse() << std::endl;
            protocol.sendstats(stats);
        }
        return stats.state;
    }
}

void ControlNotifier::run() {
    try {
        if (runLobby()) {  // Devuelve true si debe seguir.
              std::cout << "--------> SEND FIRST STATS player ind:" << player.getpos() << " "<< player.getStats().parse() << "\n"; 
              // Send first stats..
              protocol.sendstats(player.getStats());

              MatchStateType state = runGame();

              while (runPostGame(state)) {
                  state = runGame();
              }
        }
        
        std::cout << "------>ENDED NOTIFIER RUN!\n";
        // El protocol ya fue cerrado, se desconecto el cliente. por ejemplo el host al cancel, o se fue el joined.
        if(player.trydisconnect()){
             //std::cout << "-------Not Disconnected player so let receiver notify!??\n";
             //protocol.close();// just in case.
             return;
        }
        
        //std::cout << "-------NOTIFIER Lobby Disconnect "<< player.toString() <<" failed so notify!??\n";
        lobbies.disconnectFrom(match, player);
        
    } catch (const LibError&
                     error) {       // No deberia pasara realmente, antes pasaria en el controller.
        if (protocol.isactive()) {  // Si en teoria esta abierto...
            std::cerr << "player " << player.getid(0) << " notify error: " << error.what()
                      << std::endl;
            // El cerrar no deberia estar aca capaz. Si fallo el send otro fallara tmbn
        }
        
        if(player.trydisconnect()){
             //std::cout << "-------Not Disconnected player so let receiver notify!??\n";
             return;
        }
        //std::cout << "-------NOTIFIER Lobby Disconnect "<< player.toString() <<" failed so notify!??\n";
        lobbies.disconnectFrom(match, player);
    }
}


ControlNotifier::~ControlNotifier() {
    stop();
    //player.canceled();  // Por si no se cerro, cerra la queue.
    join();
}
