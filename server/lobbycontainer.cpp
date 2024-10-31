#include "./lobbycontainer.h"

#include <iostream>

#include "./gameerror.h"

LobbyContainer::LobbyContainer(): lastLobbyId(0) {}

Match& LobbyContainer::newLobby() {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    return lobbies.emplace_back(++lastLobbyId);
}

Match& LobbyContainer::findLobby(lobbyID id) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    for (auto lobbyit = lobbies.begin(); lobbyit != lobbies.end();) {
        if (lobbyit->getID() == id) {
            return *lobbyit;
        }
        ++lobbyit;
    }

    throw GameError("Not found lobby %d", id);
}

// Unirse a la lobby y esperar a que empieze. Tira error si no existe.
ControlledPlayer& LobbyContainer::joinLobby(uint8_t count, Match& lobby) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    if (lobby.isrunning()) {
        throw GameError("Tried to join already started lobby %d", lobby.getID());
    }

    return lobby.addPlayers(count);
}

// Una vez empezada no se aceptan mas.
void LobbyContainer::startLobby(Match& lobby) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    return lobby.init();
    // return findLobby(id).start();
}

void LobbyContainer::disconnectFrom(Match& lobby, ControlledPlayer& player) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.

    std::cerr << ">disconnecting " << player.toString() << std::endl;

    if (lobby.notifyDisconnect(player)) {  // Habria que liberar. No hay mas players.
        std::cerr << ">removing lobby " << lobby.getID() << std::endl;
        lobbies.remove(lobby);  // el destructor hace el finish.
    }
}

void LobbyContainer::finishAll() {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    for (auto lobbyit = lobbies.begin(); lobbyit != lobbies.end();) {
        lobbyit->finish();
        ++lobbyit;
    }
}

// Si se esta en la lobby y el anfitrion se va. Se cancela.

void LobbyContainer::cancelLobby(Match& lobby) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    if (lobby.isrunning()) {
        throw GameError("Tried to cancel already started lobby %d", lobby.getID());
    }
    lobby.cancel();
}


LobbyContainer::~LobbyContainer() { finishAll(); }
