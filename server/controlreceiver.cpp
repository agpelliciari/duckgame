#include "./controlreceiver.h"

#include <iostream>
#include <utility>

#include "./controlnotifier.h"
#include "./gameerror.h"
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
void ControlReceiver::playOn(LobbyControl& lobby) {
    try {
        // Loopeado de acciones
        while (_keep_running) {
            lobby.doaction(protocol);
        }
    } catch (const ProtocolError& error) {
        // EOF of player. No muestres nada.
    } catch (const LibError& error) {

        if (protocol.isopen()) {  // Si debiera estar activo. Error interno del protocol.
            std::cerr << "Controller lib error:" << error.what() << std::endl;
        }

    } catch (const ClosedQueue& error) {  // Para evitar llege a el catch the Thread::main
        std::cerr << "Received MATCH END " << error.what() << std::endl;
        // Envia end de la partida?
    }
}
void ControlReceiver::run() {
    ControlledPlayer player;
    LobbyControl lobbycontrol(lobbies, player, protocol);

    if (!lobbycontrol.start(protocol)) {
        std::cerr << "Could not start lobby" << std::endl;
        return;
    }

    // Inicia notifier.
    ControlNotifier notifier(player, protocol);
    notifier.start();
    playOn(lobbycontrol);

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
