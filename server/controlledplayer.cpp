#include "./controlledplayer.h"

#include <iostream>
#include <sstream>
#include <utility>

#include "./gameerror.h"

#define SIZE_SNAPSHOTS 120
#define SIZE_EVENTS 30

// Snapshots esta cerrada inicialmente. Events esta abierta.
ControlledPlayer::ControlledPlayer(const ControlId& _id, const int& _pos):id(_id),pos(_pos),isactive(true), 
events(SIZE_EVENTS, false), snapshots(SIZE_SNAPSHOTS, true){}

bool ControlledPlayer::operator==(const ControlledPlayer& other) const {
    return this->id == other.id;
}

uint8_t ControlledPlayer::playercount() const { return id.getcount(); }

const ControlId& ControlledPlayer::getcontrolid() const{
    return id;
}
int ControlledPlayer::getpos() const{
    return this->pos;
}


player_id ControlledPlayer::getid(const uint8_t ind) const { return id.get(ind); }


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
        match_stats = new_stats;
        if(snapshots.tryclose()){
            events.notifyopen();
            return true;
        }
        events.notifyopen();
        // Por ahora.. que retorne false.
        //throw GameError(SERVER_ERROR, "Inconsistent state on player, tried set lobby mode but was disconnected");
    }
    return false;
}

// Switch del player. Participando en una partida. No mas events de lobby, ahora snapshots.
bool ControlledPlayer::setgamemode(const MatchStatsInfo& new_stats) {

    if (snapshots.reopen()) {
        
        // Antes... para evitar una race condition
        match_stats = new_stats;
        
        if(events.tryclose()){
            snapshots.notifyopen();
            return true;
        }
        snapshots.notifyopen();
        
        //throw GameError(SERVER_ERROR, "Inconsistent state on player, tried set game mode but was disconnected");
    }
    return false;
}


// Para cuando el match se cancela.
bool ControlledPlayer::canceled(){
    if(match_stats.isRunning()){
        match_stats.state = CANCELADA;
    }
    return snapshots.tryclose() || events.tryclose();
}

// Se asume a lo sumo una de las dos queues estaria abierta.
bool ControlledPlayer::trydisconnect() {
    if(isactive.exchange(false)){
        snapshots.tryclose();
        events.tryclose();
        return true;
    }
    
    return false;
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
    if (id.getcount() == 1) {
        result << "Player " << (int)id.get(0);
    } else {
        result << "Players " << (int)id.get(0) << " and " << (int)id.get(1);
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
