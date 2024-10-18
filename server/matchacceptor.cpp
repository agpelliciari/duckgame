#include "./matchacceptor.h"

#include <iostream>
#include <utility>

#include "../common_src/liberror.h"


MatchAcceptor::MatchAcceptor(const char* service, Match& _match):
        sktacceptor(service), last_player(0), match(_match) {}

void MatchAcceptor::newPlayer(Socket&& connection) {

    // El ide para logs basicamente. Si bien se usa para el equal operator. Tampoco es que el equal
    // operator se use.
    PlayerController& controller = controllers.emplace_back(++last_player, match, connection);

    // start del thread notifier y controller . Ademas joinea el match en si.
    controller.init();
}
void MatchAcceptor::cleanself() {
    for (auto controlit = controllers.begin(); controlit != controllers.end();) {
        if (!controlit->isopen()) {

            // El destructor se encarga de cerrar las cosas.
            controlit = controllers.erase(controlit);
            continue;
        }

        ++controlit;
    }
}

void MatchAcceptor::disconnectAll() {
    for (auto controlit = controllers.begin(); controlit != controllers.end();) {
        controlit->finish();
        controlit = controllers.erase(controlit);
    }
}

// El thread main se encarga de catchear errores y terminar el thread.
// Pero se catchea el lib error para poner un mensaje propio.
void MatchAcceptor::run() {
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
void MatchAcceptor::init() { start(); }


void MatchAcceptor::finish() {
    if (!_keep_running) {  // Evitemos cerrar dos veces.
        return;
    }
    stop();
    sktacceptor.shutdown(2);
    sktacceptor.close();
    join();
    disconnectAll();
}


MatchAcceptor::~MatchAcceptor() { finish(); }
