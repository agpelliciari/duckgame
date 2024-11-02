#include "./controlnotifier.h"

#include <iostream>

#include "common/core/liberror.h"

ControlNotifier::ControlNotifier(Match& _match, ControlledPlayer& _player,
                                 ServerProtocol& _protocol):
        match(_match), player(_player), protocol(_protocol) {}

bool ControlNotifier::runLobby() {
    std::cerr << "Lobby notifier start!" << std::endl;
    try {
        lobby_info info = player.popinfo();
        while (_keep_running && info.action != LobbyResponseType::GAME_ERROR &&
               info.action != LobbyResponseType::STARTED_LOBBY) {


            std::cerr << "Configuration info? " << (int)info.action << ", num: " << (int)info.data
                      << std::endl;

            // protocol.notifyevent(info);
            info = player.popinfo();
        }

        if (_keep_running) {
            std::cerr << "Response start! " << (int)info.action << ", num: " << (int)info.data
                      << std::endl;
            protocol.notifyevent(info);
            return false;
        }

        std::cerr << "Closed notifier before match start" << std::endl;
        protocol.notifyinfo(LobbyResponseType::GAME_ERROR, LobbyGameErrorType::UNKNOWN);
        protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
        return true;
    } catch (const ClosedQueue& error) {
        if (match.isrunning()) {
            std::cerr << "Start from queue closed/state change?? " << std::endl;
            // se empezo.
            protocol.notifyinfo(LobbyResponseType::STARTED_LOBBY, match.playercount());
            return false;
        }
        // se cancelo.
        protocol.notifyinfo(LobbyResponseType::GAME_ERROR, LobbyGameErrorType::ANFITRION_LEFT);
        protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
        return true;
    }
}


bool ControlNotifier::runGame() {
    try {
        while (_keep_running) {
            protocol.sendstate(player.popstate());
        }
        return true;
    } catch (const ClosedQueue& error) {
        std::cerr << "Se finalizo el match... deberia mandar las estadisticas!" << std::endl;
        protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
        return true;       // Se cerro el game
    }
}

void ControlNotifier::run() {
    try {
        if (runLobby()) {  // Devuelve si se cancelo la partida/no deberia seguir.
            return;
        }

        runGame();
    } catch (const LibError&
                     error) {     // No deberia pasara realmente, antes pasaria en el controller.
        if (protocol.isopen()) {  // Si en teoria esta abierto...
            std::cerr << "player " << player.getid(0) << " notify error: " << error.what()
                      << std::endl;

            // El cerrar no deberia estar aca capaz. Si fallo el send otro fallara tmbn
        }
    }
}


ControlNotifier::~ControlNotifier() {
    stop();
    player.disconnect();  // Por si no se cerro, cerra la queue.
    join();
}
