#include "./playeracceptor.h"

#include <iostream>
#include <utility>

#include "common/liberror.h"


PlayerAcceptor::PlayerAcceptor(const char* service, LobbyContainer& _lobbies):
        sktacceptor(service), last_player(0), lobbies(_lobbies) {}

void PlayerAcceptor::newPlayer(Socket&& connection) {

    // El ide para logs basicamente. Si bien se usa para el equal operator. Tampoco es que el equal
    // operator se use.
    PlayerController& controller = controllers.emplace_back(++last_player, lobbies, connection);

    // start del thread notifier y controller . Ademas joinea el match en si.
    controller.init();
}
void PlayerAcceptor::cleanself() {
    for (auto controlit = controllers.begin(); controlit != controllers.end();) {
        if (!controlit->isopen()) {

            // El destructor se encarga de cerrar las cosas.
            controlit = controllers.erase(controlit);
            continue;
        }

        ++controlit;
    }
}

void PlayerAcceptor::disconnectAll() {
    for (auto controlit = controllers.begin(); controlit != controllers.end();) {
        controlit->finish();
        controlit = controllers.erase(controlit);
    }
}

// El thread main se encarga de catchear errores y terminar el thread.
// Pero se catchea el lib error para poner un mensaje propio.
void PlayerAcceptor::run() {
    // Espera nuevos jugadores infinitamente? no parece haber limite.
    try {
        while (_keep_running) {
            newPlayer(sktacceptor.accept());
            cleanself();
        }
    } catch (const LibError& error) {
        std::cerr << "Closing server: " << error.what() << std::endl;
    }
}
void PlayerAcceptor::init() { start(); }

bool PlayerAcceptor::isrunning(){
     return is_alive();
}

void PlayerAcceptor::finish() {
    if (!_keep_running) {  // Evitemos cerrar dos veces.
        return;
    }
    stop();
    sktacceptor.shutdown(2);
    sktacceptor.close();
    join();
    disconnectAll();
}


PlayerAcceptor::~PlayerAcceptor() { finish(); }
