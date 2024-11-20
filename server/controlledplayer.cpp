#include "./controlledplayer.h"

#include <iostream>
#include <sstream>
#include <utility>

#include "./gameerror.h"

#define SIZE_SNAPSHOTS 120
#define SIZE_EVENTS 30

// Snapshots esta cerrada inicialmente. Events esta abierta.
ControlledPlayer::ControlledPlayer(player_id first):
        count(1), ids(), events(SIZE_EVENTS, false), snapshots(SIZE_SNAPSHOTS, true) {
    ids[0] = first;
    ids[1] = first;
}

ControlledPlayer::ControlledPlayer(player_id first, player_id second):
        count(2), ids(), events(SIZE_EVENTS, false), snapshots(SIZE_SNAPSHOTS, true) {
    ids[0] = first;
    ids[1] = second;
}

bool ControlledPlayer::operator==(const ControlledPlayer& other) const {
    return this->ids[0] == other.ids[0] && this->ids[1] == other.ids[1];
}

uint8_t ControlledPlayer::playercount() const { return this->count; }


player_id ControlledPlayer::getid(const uint8_t ind) const { return this->ids[ind]; }


// Switch del player. Participando en una partida. No mas events de lobby, ahora snapshots.
bool ControlledPlayer::setgamemode() {
    if (snapshots.reopen()) {
        match_stats.state = STARTED_ROUND;
        match_stats.numronda++;
        // Antes... para evitar una race condition
        if(events.tryclose()){
            return true;
        }
        throw GameError(SERVER_ERROR, "Inconsistent state on player, tried set game mode but was disconnected");
    }
    return false;
}

void ControlledPlayer::waitgamemode(){
     snapshots.waitreopen();
}
void ControlledPlayer::waitlobbymode(){
     events.waitreopen();
}


const MatchStatsInfo& ControlledPlayer::getStats(){
      snapshots.resetdirty(); // Saca el dirty para notificar que se vio las stats.
      return match_stats;
}

// Switch del player. Participando a la lobby. No mas snapshots ahora events de lobby.
bool ControlledPlayer::setlobbymode(const MatchStatsInfo& new_stats) {    
    if (events.reopen()) {
        if(snapshots.tryclose()){
            match_stats = new_stats;
            return true;
        }
        throw GameError(SERVER_ERROR, "Inconsistent state on player, tried set lobby mode but was disconnected");
    }
    return false;
}



// Se asume a lo sumo una de las dos queues estaria abierta.
bool ControlledPlayer::disconnect() {
    match_stats.state = CANCELADA;
    return snapshots.tryclose() || events.tryclose();
}

// No hace falta sincronizar/lockear ya que si se llama a este metodo
// La queue sigue abierta. Y no nos importa en todo caso mandar un evento extra o no.
// O eso se dio a
bool ControlledPlayer::recvstate(const MatchDto& state) {
    try{
        snapshots.try_push(state);
        return true;
    } catch(const ClosedQueue& error){
        return false;
    }
}

// Se podria hacer de forma polimorfica/delegatoria seguro.
MatchDto ControlledPlayer::popstate() {
    snapshots.checkdirty();
    return snapshots.pop(); 
}


std::string ControlledPlayer::toString() {
    std::stringstream result;
    if (count == 1) {
        result << "Player " << (int)ids[0];
    } else {
        result << "Players " << (int)ids[0] << " and " << (int)ids[1];
    }

    return result.str();
}


// recveinfo es no bloqueante! Recibe el lobby info con try_push a la queue del player
// Todo es "bloqueante" por posibles locks... pero bueno
bool ControlledPlayer::recvinfo(const lobby_info& dto) {
    try{
        events.try_push(dto);
        return true;
    } catch(const ClosedQueue& error){
        return false;
    }
}

// Pop lobby info. Bloqueante. Si no hay eventos espera a uno.
lobby_info ControlledPlayer::popinfo() { return events.pop(); }


/// La verdad no deberia pasar no.
// ControlledPlayer::~ControlledPlayer(){
//      disconnect();
// }
