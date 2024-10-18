#include "./match.h"

#include <iostream>

#include "unistd.h"

static const int SLEEP_TIME = 1000 * 200;  // 200ms

Match::Match(PlayerContainer& _players): players(_players), state(players) {}

// Metodos delegatorios.
void Match::notifyAction(const MatchAction&& action) { actions.notify(action); }

void Match::run() {
    while (_keep_running) {      // Mientras deba ejecutarse.
        state.step();            // non player logic.
        actions.applyOn(state);  // player logic

        usleep(SLEEP_TIME);
    }
}

void Match::init() { start(); }
bool Match::isrunning() { return _is_alive; }

void Match::finish() {
    if (!_keep_running) {  // Evitemos cerrar dos veces.
        return;
    }
    stop();
    actions.close();
    players.removeAll();

    join();
}


Match::~Match() { finish(); }
