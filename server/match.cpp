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
    if (player.disconnect()) {
        // Si se esta desconectando ahora entonces notifica.
        std::cout << "Disconnected player from match? now " << connectedplayers << std::endl;
        if (_keep_running) {
            return connectedplayers == 0;
        }

        players.remove(player);
    }
    return connectedplayers == 0;
}

void Match::init() {
    if (is_alive()) {
        throw GameError(LOBBY_ALREADY_STARTED, "Tried to start a match already started!!\n");
    }
    looper.start_players(players);
    players.finishLobbyMode();
    start();
    // match_start.notify_all();
}

bool Match::hostLobbyLeft(ControlledPlayer& host) {
    connectedplayers--;
    if (connectedplayers == 0) {
        host.disconnect();
        return true;
    }
    // Notifica a los otros ademas del disconnect.
    host.disconnect();
    players.hostLobbyLeft(host);

    return false;
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

    // notifica los playeres. Del final.
    players.forceDisconnectAll();
}

bool Match::isrunning() const { return _is_alive; }


void Match::finish() {
    if (_keep_running) {
        stop();
        looper.stop();
        join();
        return;
    }
    // El finish en caso de no estar corriendo.
    // Asume que se esta en lobby mode.
    players.forceDisconnectAll();
}

Match::~Match() {
    if (_keep_running) {
        stop();
        looper.stop();
        join();
    }
}
