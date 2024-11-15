#include "./controlnotifier.h"

#include <iostream>

#include "common/core/liberror.h"

ControlNotifier::ControlNotifier(Match& _match, ControlledPlayer& _player,
                                 ServerProtocol& _protocol):
        match(_match), player(_player), protocol(_protocol) {}

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
        return true;
    } catch (const ClosedQueue& error) {

        if (!protocol.isactive()) {
            // Se presiono la q. O es host.. ya se cerro el protocol.
            return true;
        }

        // Si el player esta closed, el match fue cancelado
        // Ya que para participar en el mismo deberia estar abierto.
        if (player.isclosed()) {
            std::cout << "-----------> ESTO PASA?!\n";
            protocol.notifyinfo(LobbyResponseType::GAME_ERROR, LobbyErrorType::SERVER_ERROR);
            protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
            return true;
        }

        protocol.notifyinfo(LobbyResponseType::STARTED_LOBBY, match.playercount());

        protocol.sendmapinfo(match.getMap());
        return false;
    }
}


bool ControlNotifier::runPostGame(MatchStateType state){
    if(state == TERMINADA || state == CANCELADA){
        std::cout << "NOTIFIER ENDED OR CANCELED MATCH!\n";
        protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
        return false;       // Se cerro el game
    }
    
    if(state == INICIADA || state == ROUND_END){
         return true;
    }
    
    try {
        std::cout << "NOTIFIER PAUSED MATCH FOR 5 seconds?!\n";
            
        lobby_info info = player.popinfo();
        // its paused!
        while (_keep_running) {


            std::cerr << "pause m " << (int)match.getID() << " info to " << player.toString() << "? "
                      << (int)info.action << ", num: " << (int)info.data << std::endl;

            //protocol.notifyevent(info);

            if (info.action == LobbyResponseType::MATCH_PAUSE_END) {
                return true;  // Pause end... continue?!
            }

            info = player.popinfo();
        }        
        
        return false;
    } catch (const ClosedQueue& error) {
        std::cout << "CLOSED QUEUE AT POST ROUND/GAME??\n";
        protocol.close();// Closed?
        return false;
    }

}
MatchStateType ControlNotifier::runGame() {
    std::cerr << "#game notify for " << player.toString() << " at match " << (int)match.getID()
              << " start!" << std::endl;
    try {
        while (_keep_running) {
            protocol.sendstate(player.popstate());
        }
        
        return CANCELADA;
    } catch (const ClosedQueue& error) {
        const MatchStatsInfo& stats = match.getStats();
        protocol.sendstats(stats);
        return stats.state;
    }
}

void ControlNotifier::run() {
    try {
        if (runLobby()) {  // Devuelve si se cancelo la partida/no deberia seguir.
            return;
        }

        MatchStateType state = runGame();
        
        while(runPostGame(state)){
             state = runGame();
        }
    } catch (const LibError&
                     error) {       // No deberia pasara realmente, antes pasaria en el controller.
        if (protocol.isactive()) {  // Si en teoria esta abierto...
            std::cerr << "player " << player.getid(0) << " notify error: " << error.what()
                      << std::endl;

            // El cerrar no deberia estar aca capaz. Si fallo el send otro fallara tmbn
        }
    }
}


ControlNotifier::~ControlNotifier() {
    stop();
    // player.disconnect();  // Por si no se cerro, cerra la queue.
    join();
}
