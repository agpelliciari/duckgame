#include "./match.h"

#include <iostream>

#include "./gameerror.h"

#include "unistd.h"

static const int SLEEP_TIME = 1000 * 200;  // 200ms

Match::Match(lobbyID _id): id(_id), players(), state() {}


// Protected// friend accessed methods
void Match::addPlayer(Player* player) { players.add(player); }

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
    players.removeAll();
    actions.close();

    join();
}


// General/public methods.

bool Match::operator==(const Match& other) const { return this->id == other.id; }


lobbyID Match::getID() const { return this->id; }

// Metodos delegatorios.
void Match::notifyAction(const MatchAction&& action) {
    if (_keep_running) {
        actions.notify(action);
    }
}

void Match::run() {
    // bool matchcontinues = true;
    while (_keep_running) {
        // while (_keep_running && matchcontinues) {      // Mientras deba ejecutarse.
        state.step();            // non player logic.
        actions.applyOn(state);  // player logic

        players.updateState(state);

        usleep(SLEEP_TIME);
    }
    // Checkea si el finish fue natural o forzado.
}

bool Match::isrunning() const { return _is_alive; }

Match::~Match() { finish(); }
