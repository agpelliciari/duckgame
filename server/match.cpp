#include "./match.h"

#include <iostream>

#include "./gameerror.h"

Match::Match(lobbyID _id): id(_id), players(), looper(), connectedplayers(0) {}


// Protected// friend accessed methods
ControlledPlayer& Match::addPlayers(uint8_t count) {
    connectedplayers++;  // Solo importa la cantidad de conectados
    return players.add(count);
}
int Match::playercount() const { return players.playercount(); }


bool Match::notifyDisconnect(ControlledPlayer& player) {
    connectedplayers--;  // Solo importa la cantidad de conectados

    player.disconnect();

    return connectedplayers == 0;  // Deberia liberar?
}

void Match::init() {
    if (is_alive()) {
        throw GameError("Tried to start a match already started!!\n");
    }
    start();
    players.finishLobbyMode();
    // match_start.notify_all();
}

void Match::cancel() {
    players.finishLobbyMode();
    // match_start.notify_all();
}


void Match::finish() {
    if (!_keep_running) {  // Evitemos cerrar dos veces.
        return;
    }
    stop();
    looper.stop();
    join();
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

    // notifica los playeres.
    players.removeAll();
}

bool Match::isrunning() const { return _is_alive; }

Match::~Match() { finish(); }
