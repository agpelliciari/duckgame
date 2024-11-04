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
        while (_keep_running && info.action != LobbyResponseType::GAME_ERROR &&
               info.action != LobbyResponseType::STARTED_LOBBY) {


            std::cerr << "Configuration info to " << player.toString() << "? " << (int)info.action
                      << ", num: " << (int)info.data << std::endl;

            protocol.notifyevent(info);
            info = player.popinfo();
        }

        if (_keep_running) {
            std::cerr << "Response start! " << (int)info.action << ", num: " << (int)info.data
                      << std::endl;
            protocol.notifyevent(info);
            return false;
        }

        std::cerr << "Closed notifier before match start" << std::endl;
        protocol.notifyinfo(LobbyResponseType::GAME_ERROR, LobbyErrorType::UNKNOWN);
        protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
        return true;
    } catch (const ClosedQueue& error) {

        // Si el player esta closed, el match fue cancelado
        // Ya que para participar en el mismo deberia estar abierto.
        if (player.isclosed()) {
            // se cancelo.
            protocol.notifyinfo(LobbyResponseType::GAME_ERROR, LobbyErrorType::ANFITRION_LEFT);
            protocol.close();  // Si no esta cerrado, cerralo, asi se sale el controller tambien.
            return true;
        }

        protocol.notifyinfo(LobbyResponseType::STARTED_LOBBY, match.playercount());

        return false;
    }
}


bool ControlNotifier::runGame() {
    std::cerr << "#game notify for " << player.toString() << " at match " << (int)match.getID()
              << " start!" << std::endl;
    try {
        while (_keep_running) {
            protocol.sendstate(player.popstate());
        }
        return true;
    } catch (const ClosedQueue& error) {

        if (!match.isrunning()) {
            std::cerr << "Se finalizo el match... deberia mandar las estadisticas!" << std::endl;
        }
        // std::cerr << "CLOSED QUEUE? FOR GAME MODE" << std::endl;

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
    player.disconnect();  // Por si no se cerro, cerra la queue.
    join();
}
