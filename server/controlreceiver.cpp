#include "./controlreceiver.h"

#include <iostream>
#include <utility>

#include "./controlnotifier.h"
#include "./gameerror.h"
#include "common/liberror.h"


ControlReceiver::ControlReceiver(LobbyContainer& _lobbies, Socket& skt):
        lobbies(_lobbies), protocol(std::move(skt)) {}


bool ControlReceiver::isopen() { return protocol.isopen(); }

void ControlReceiver::init() {
    if (_is_alive) {
        throw GameError("Tried to init player notifier/controller when already inited.");
    }
    start();
}

void ControlReceiver::playOn(ControlledPlayer& player, Match& match) {
    player.open();

    // Inicia notifier.
    ControlNotifier notifier(player, protocol);
    notifier.start();
    try {

        // Loopeado de acciones


        while (_keep_running) {
            match.notifyAction(protocol.recvaction());
        }
        player.disconnect();  // Finalizo normalmente.
    } catch (const LibError& error) {
        if (player.disconnect() && protocol.isopen()) {  // Si desconecto. Hubo error aca.
            std::cerr << "Controller lib error:" << error.what() << std::endl;
        }
    } catch (const GameError& error) {  // EOF, el notify se asume no genera exception.
        player.disconnect();
    } catch (const ClosedQueue& error) {  // EOF, el notify se asume no genera exception.
        std::cerr << "Controller MATCH END " << error.what() << std::endl;
        player.disconnect();
    }

    notifier.stop();
    notifier.join();

    // El log a cerr podria ser innecesario. Pero sirve para hacer cosas mas descriptivas.
    std::cerr << ">closed Player " << player.getid(0) << std::endl;
    if (player.playercount() > 1) {
        std::cerr << ">closed Player " << player.getid(1) << std::endl;
    }
}


void ControlReceiver::handleNewLobby(const uint8_t playercount) {
    ControlledPlayer player;
    player.setplayercount(playercount);

    Match& match = lobbies.newLobby(&player);
    std::cerr << "New lobby id: " << (int)match.getID() << std::endl;

    if (!protocol.recvsignalstart()) {
        std::cerr << "CANCELED LOBBY: " << (int)match.getID() << std::endl;
        // Close lobby
        lobbies.stopLobby(match);
        return;
    }
    std::cerr << "Started lobby id: " << (int)match.getID() << std::endl;
    lobbies.startLobby(match);

    // Es no except.
    playOn(player, match);

    // Close lobby on exit of anfitrion?
    lobbies.stopLobby(match);
}

void ControlReceiver::run() {
    try {
        uint8_t playercount;
        if (!protocol.recvplayercount(&playercount)) {
            std::cerr << "Player controller aborted" << std::endl;
            return;  // Permitamos que se desconecte inicialmente si no se manda el count.
        }
        lobby_action info = protocol.recvlobbyaction();
        if (info.action == NEW_LOBBY) {
            handleNewLobby(playercount);
        } else {  // Handle de join lobby.
            ControlledPlayer player;
            player.setplayercount(playercount);
            std::cerr << "Connected lobby info join lobby " << (int)info.attached_id << std::endl;
            playOn(player, lobbies.joinLobby(&player, info.attached_id));
        }
    } catch (const LibError& error) {
        std::cerr << "Lobby lib error:" << error.what() << std::endl;
    } catch (const GameError& error) {  // .
        std::cerr << "Lobby game error:" << error.what() << std::endl;
    }
}

// Este metodo no hace acciones irreversibles
// Tal que vos podrias re empezar los threads devuelta. Reconectar.
void ControlReceiver::finish() {
    // Como solo el controller modifica el keep running/llama a stop sirve
    // para saber si todavia no se termino
    if (!_keep_running) {
        return;
    }

    // Se encarga el protocol de verificar solo sea cerrado una vez.
    protocol.close();

    stop();


    // Joins
    join();
}

ControlReceiver::~ControlReceiver() { finish(); }
