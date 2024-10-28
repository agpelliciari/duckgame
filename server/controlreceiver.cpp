#include "./controlreceiver.h"

#include <iostream>
#include <utility>

#include "./controlnotifier.h"
#include "./gameerror.h"
#include "./lobbycontrol.h"
#include "common/core/liberror.h"
#include "common/protocolerror.h"


ControlReceiver::ControlReceiver(LobbyContainer& _lobbies, Socket& skt):
        lobbies(_lobbies), protocol(skt) {}


bool ControlReceiver::isopen() { return protocol.isopen(); }

void ControlReceiver::init() {
    if (_is_alive) {
        throw GameError("Tried to init player notifier/controller when already inited.");
    }
    start();
}
void ControlReceiver::playOn(const ControlledPlayer& player, Match& match) {
    try {
        // Loopeado de acciones
        while (_keep_running) {
            PlayerActionDTO action = protocol.recvaction();
            if (player.playercount() <= action.playerind) {
                std::cerr << "Invalid action from client!!\n";
                return;
            }
            action.playerind = player.getid(action.playerind);
            match.notifyAction(action);
        }
    } catch (const ProtocolError& error) {
        // EOF of player. No muestres nada.
    } catch (const LibError& error) {
        if (protocol.isopen()) {  // Si debiera estar activo. Error interno del protocol.
            std::cerr << "Controller lib error:" << error.what() << std::endl;
        }
    } catch (const std::exception& err) {
        std::cerr << "excep : " << err.what() << " Ending control receiver.\n";
    } catch (...) {
        std::cerr << "excep <unknown> Ending control receiver.\n";
    }
}
void ControlReceiver::run() {
    LobbyControl lobby(lobbies, protocol);

    bool isanfitrion;
    Match& match = lobby.resolveMatch(&isanfitrion);
    ControlledPlayer& player = isanfitrion ? lobby.start(match) : lobby.waitStart(match);

    // Inicia notifier.
    ControlNotifier notifier(player, protocol);
    notifier.start();

    playOn(player, match);  // Es no except.

    player.disconnect();
    if (isanfitrion) {
        lobbies.stopLobby(match);
    }

    // El log a cerr podria ser innecesario. Pero sirve para hacer cosas mas descriptivas.
    std::cerr << ">closed " << player.toString() << std::endl;
    // El destructor de notifier hace join.
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
