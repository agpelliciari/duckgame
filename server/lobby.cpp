#include "./lobby.h"

#include <iostream>

#include "unistd.h"
#include "./gameerror.h"

Lobby::Lobby(lobbyID _id): id(_id), match(players) {}

lobbyID Lobby::getID() const{
       return this->id;
}

bool Lobby::operator==(const Lobby& other) const{
     return this->id == other.getID();
}



void Lobby::addPlayer(Player* player) { players.add(player); }

Match& Lobby::waitStart(std::unique_lock<std::mutex>& lock){
     match_started.wait(lock);
     return match;
}

Match& Lobby::start() {
    if(isrunning()){
         throw new GameError("Tried init already inited lobby");
    }
    
    match.init();
    match_started.notify_all();
    return match;
}

bool Lobby::isrunning() { return match.isrunning(); }

void Lobby::finish() {
    match.finish();
}

Lobby::~Lobby() { finish(); }
