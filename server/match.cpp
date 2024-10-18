#include "./match.h"

#include <iostream>

#include "unistd.h"

static const int SLEEP_TIME = 1000 * 200;  // 200ms

Match::Match(PlayerContainer& _players): players(_players), state() {}

// Metodos delegatorios.
void Match::notifyAction(const MatchAction&& action) { actions.notify(action); }

void Match::run() {
    //bool matchcontinues = true;
    while (_keep_running) { 
    //while (_keep_running && matchcontinues) {      // Mientras deba ejecutarse.
        state.step();            // non player logic.
        actions.applyOn(state);  // player logic
        
        players.updateState(state);
        
        usleep(SLEEP_TIME);
    }
    // Checkea si el finish fue natural o forzado.
    
}

void Match::init() { start(); }
bool Match::isrunning() { return _is_alive; }

void Match::finish() {
    if (!_keep_running) {  // Evitemos cerrar dos veces.
        return;
    }
    stop();
    players.removeAll();
    actions.close();

    join();
}


Match::~Match() { finish(); }
