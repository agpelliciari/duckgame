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
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    if (is_alive()) {
        throw GameError("Tried to start a match already started!!\n");
    }
    start();
    match_start.notify_all();
}

void Match::cancel() {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    match_start.notify_all();
}


void Match::finish() {
    if (!_keep_running) {  // Evitemos cerrar dos veces.
        return;
    }
    stop();
    looper.stop();
    join();
}

void Match::waitStart() {
    std::unique_lock<std::mutex> lck(mtx);
    if (_keep_running) {
        return;
    }
    match_start.wait(lck);
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
