#include "./lobbycontainer.h"

#include <iostream>

#include "./gameerror.h"

#define MAX_COUNT_MATCH 4

LobbyContainer::LobbyContainer(): lastLobbyId(0) {}
LobbyContainer::LobbyContainer(const char* maps_root): lastLobbyId(0),maps(maps_root) {}


const std::vector<std::string>& LobbyContainer::registeredMaps() const{
    return maps.registeredMaps();
}


int LobbyContainer::countMatches() {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    return lobbies.size();
}
int LobbyContainer::countPlayers(Match& match){
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    return match.playercount();
}


Match& LobbyContainer::findLobby(lobbyID id) {
    for (auto lobbyit = lobbies.begin(); lobbyit != lobbies.end();) {
        if (lobbyit->getID() == id) {
            return *lobbyit;
        }
        ++lobbyit;
    }

    throw GameError(LOBBY_NOT_FOUND, "Not found lobby %d", id);
}

Match& LobbyContainer::newLobby(ControlId& out) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    Match& lobby = lobbies.emplace_back(++lastLobbyId, MAX_COUNT_MATCH);
    lobby.addPlayers(out);
    return lobby;
}


// Unirse a la lobby y esperar a que empieze. Tira error si no existe.
Match& LobbyContainer::joinLobby(lobbyID id, ControlId& out, std::vector<player_id>& players) {
    
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    Match& lobby = findLobby(id);
    
    if (lobby.canaddplayer()) {
    
        lobby.addPlayers(out);
        
        lobby.putPlayers(players);
        
        return lobby;
    }
    
    throw GameError(LOBBY_ALREADY_STARTED, "Tried to join already started lobby %d",
                    lobby.getID());
}

// Una vez empezada no se aceptan mas.
void LobbyContainer::startLobby(Match& lobby, const char* mapname) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    return lobby.init(maps, mapname);
    // return findLobby(id).start();
}


ControlledPlayer& LobbyContainer::getPlayerOn(Match& lobby,  const ControlId& id) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    return lobby.getPlayer(id);
}
void LobbyContainer::disconnectFrom(Match& lobby, ControlledPlayer& player) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    // std::cerr << ">disconnecting " << player.toString() << std::endl;

    if (lobby.notifyDisconnect(player)) {  // Habria que liberar. No hay mas players.
        std::cerr << ">removing lobby " << lobby.getID() << std::endl;
        lobby.finish(maps);

        lobbies.remove(lobby);  // el destructor hace el finish.
    }
}

void LobbyContainer::finishAll() {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    for (auto lobbyit = lobbies.begin(); lobbyit != lobbies.end();) {
        lobbyit->finish(maps);
        ++lobbyit;
    }
}

// Si se esta en la lobby y el anfitrion se va. Se cancela.
void LobbyContainer::hostLeft(Match& lobby, ControlledPlayer& host) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    if (lobby.isrunning()) {
        throw GameError(LOBBY_ALREADY_STARTED, "Tried to cancel already started lobby %d",
                        lobby.getID());
    }
    if (lobby.hostLobbyLeft(host)) {
        std::cerr << ">removing lobby " << lobby.getID() << " cancel" << std::endl;
        lobbies.remove(lobby);  // el destructor hace el finish.
    }
}
void LobbyContainer::errorOnLobby(Match& lobby, LobbyErrorType error) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on container.
    if (lobby.isrunning()) {
        throw GameError(LOBBY_ALREADY_STARTED,
                        "Tried to notify lobby error on already started lobby %d", lobby.getID());
    }
    lobby.cancelByError(error);
}


LobbyContainer::~LobbyContainer() { finishAll(); }
