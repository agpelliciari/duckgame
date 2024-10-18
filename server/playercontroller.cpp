#include "./playercontroller.h"

#include <iostream>
#include <utility>

#include "common/liberror.h"
#include "./gameerror.h"


PlayerController::PlayerController(player_id ide, Match& _match, Socket& skt):
        match(_match), player(ide), protocol(std::move(skt)), notifier(player, protocol) {}


bool PlayerController::isopen() { return player.isopen(); }


void PlayerController::init() {
    if (_is_alive) {
        throw GameError("Tried to init player notifier/controller when already inited.");
    }

    // Join/add player to match.
    match.addPlayer(&player);

    // Asegurado, en teoria, que tampoco esta empezado.
    notifier.start();
    start();
}

void PlayerController::run() {
    try {

        // Se podria checkear que el player siga abierto tambien
        // Pero no hace falta, en todo caso fallara el recvpickup
        while (_keep_running) {
            match.notifyAction(protocol.recvpickup());
        }
        player.disconnect();  // Finalizo normalmente.
    } catch (const LibError& error) {
        if (player.disconnect()) {  // Si desconecto. Hubo error aca.
            std::cerr << "Controller lib error:" << error.what() << std::endl;
        }
    } catch (const GameError& error) {  // EOF, el notify se asume no genera exception.
        player.disconnect();
    }

    // Sea por la razon que fuere. Notifica/remove el player.
    match.removePlayer(&player);

    // El log a cerr podria ser innecesario. Pero sirve para hacer cosas mas descriptivas.
    std::cerr << ">closed Player " << player.getid() << std::endl;
}

// Este metodo no hace acciones irreversibles
// Tal que vos podrias re empezar los threads devuelta. Reconectar.
void PlayerController::finish() {
    // Como solo el controller modifica el keep running/llama a stop sirve
    // para saber si todavia no se termino
    if (!_keep_running) {
        return;
    }

    // Joins
    stop();
    notifier.stop();

    join();
    notifier.join();
}

PlayerController::~PlayerController() {


    // Esta logica esta fuera del finish en si
    // Ya que la idea es que el finish no libere en si las cosas.
    if (player.disconnect()) {
        // Player estaba activo, cerra sin esperar a que terminen las acciones
        // Como podria ser el read de una accion o el envio de un evento.
        protocol.close();
    }

    finish();
}
