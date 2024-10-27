#include "./match.h"

#include <iostream>

#include "./gameerror.h"

Match::Match(lobbyID _id): id(_id), players(), looper() {}


// Protected// friend accessed methods
ControlledPlayer& Match::addPlayers(uint8_t count) { return players.add(count); }

void Match::init() {
    if (is_alive()) {
        throw GameError("Tried to start a match already started!!\n");
    }
    start();
}

void Match::finish() {
    if (!_keep_running) {  // Evitemos cerrar dos veces.
        return;
    }
    stop();
    looper.stop();
    join();

    // libera los players/listeners.
    // Despues de joinear para asegurar no le removes nada en el medio.
    players.removeAll();
}


// General/public methods.

bool Match::operator==(const Match& other) const { return this->id == other.id; }


lobbyID Match::getID() const { return this->id; }

// Metodos delegatorios.
void Match::notifyAction(const PlayerActionDTO& action) {
    if (_keep_running) {
        looper.pushAction(action);
    }
}

void Match::run() {

    looper.loop(players);
    // Checkea si el finish fue natural o forzado.
}

bool Match::isrunning() const { return _is_alive; }

Match::~Match() { finish(); }
