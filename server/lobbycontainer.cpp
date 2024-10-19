#include "./lobbycontainer.h"

#include <iostream>

#include "./gameerror.h"

LobbyContainer::LobbyContainer(): lastLobbyId(0) {}

Match& LobbyContainer::newLobby(Player* player) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    Match& lobby = lobbies.emplace_back(++lastLobbyId);
    lobby.addPlayer(player);

    return lobby;
}

Match& LobbyContainer::findLobby(lobbyID id) {
    for (auto lobbyit = lobbies.begin(); lobbyit != lobbies.end();) {
        if (lobbyit->getID() == id) {
            return *lobbyit;
        }
        ++lobbyit;
    }

    throw GameError("Not found lobby %d", id);
}

// Unirse a la lobby y esperar a que empieze. Tira error si no existe.
Match& LobbyContainer::joinLobby(Player* player, lobbyID id) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    Match& lobby = findLobby(id);
    if (lobby.isrunning()) {
        throw GameError("Tried to join already started lobby %d", id);
    }

    lobby.addPlayer(player);
    return lobby;
}
// Una vez empezada no se aceptan mas.
void LobbyContainer::startLobby(Match& lobby) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    return lobby.init();
    // return findLobby(id).start();
}


void LobbyContainer::stopLobby(const Match& lobby) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    lobbies.remove(lobby);                  // el destructor hace el finish.
}

void LobbyContainer::finishAll() {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    for (auto lobbyit = lobbies.begin(); lobbyit != lobbies.end();) {
        lobbyit->finish();
        ++lobbyit;
    }
}
LobbyContainer::~LobbyContainer() { finishAll(); }
