#include "./lobbycontainer.h"
#include "./gameerror.h"

#include <iostream>

LobbyContainer::LobbyContainer(): lastLobbyId(0) {}

lobbyID LobbyContainer::newLobby(Player* player) {
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    Lobby& lobbie = lobbies.emplace_back(++lastLobbyId);
    lobbie.addPlayer(player);
    
    return lastLobbyId;
}

Lobby& LobbyContainer::findLobby(lobbyID id){
    for (auto lobbyit = lobbies.begin(); lobbyit != lobbies.end();) {
        if(lobbyit->getID() == id){
             return *lobbyit;
        }
        ++lobbyit;
    }
    
    throw new GameError("Not found lobby %d", id);
}

// Unirse a la lobby y esperar a que empieze. Tira error si no existe.
Match& LobbyContainer::joinLobby(Player* player, lobbyID id){
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    Lobby& lobbie = findLobby(id);
    if(lobbie.isrunning()){
          throw new GameError("Tried to join already started lobby %d", id);
    }
    
    lobbie.addPlayer(player);
    return lobbie.waitStart(lck);
}
// Una vez empezada no se aceptan mas.
Match& LobbyContainer::startLobby(lobbyID id){
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    return findLobby(id).start();
}


void LobbyContainer::stopLobby(lobbyID id){
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    Lobby& lobby = findLobby(id);
    if(lobby.isrunning()){
          lobby.finish();
    }
    
    lobbies.remove(lobby);
}

void LobbyContainer::finishAll(){
    std::unique_lock<std::mutex> lck(mtx);  // No other actions on lobby.
    for (auto lobbyit = lobbies.begin(); lobbyit != lobbies.end();) {
        lobbyit->finish();
        ++lobbyit;
    }
}
LobbyContainer::~LobbyContainer(){
     finishAll();
}

