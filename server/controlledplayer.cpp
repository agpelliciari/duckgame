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
    std::unique_lock<std::mutex> lck(mtx);
    if(events.isclosed()){
       return false;
    }
    
    if (snapshots.reopen()) {
        events.close();
        return true;
    }
    return false;
}

// Switch del player. Participando a la lobby. No mas snapshots ahora events de lobby.
bool ControlledPlayer::setlobbymode() {
    std::unique_lock<std::mutex> lck(mtx);
    if(snapshots.isclosed()){
       return false;
    }
    
    if (events.reopen()) {
        snapshots.close();
        return true;
    }
    return false;
}

/*
// Capaz por ahora no hace falta sincronizar
// Pero mejor ser precavido sobre posibles race conditions.
bool ControlledPlayer::islobbymode() {
    std::unique_lock<std::mutex> lck(mtx);
    return !(events.isclosed());
}

bool ControlledPlayer::isgamemode() {
    std::unique_lock<std::mutex> lck(mtx);
    return !(snapshots.isclosed());
}
*/

bool ControlledPlayer::isclosed() {
    std::unique_lock<std::mutex> lck(mtx);
    return snapshots.isclosed() && events.isclosed();
}

bool ControlledPlayer::disconnect() {
    std::unique_lock<std::mutex> lck(mtx);
    if (snapshots.isclosed()) {
        if (events.isclosed()) {
            return false;
        }
        
        events.close();
        return true;
    }
    
    snapshots.close();
    return true;
}

// No hace falta sincronizar/lockear ya que si se llama a este metodo
// La queue sigue abierta. Y no nos importa en todo caso mandar un evento extra o no.
// O eso se dio a
bool ControlledPlayer::recvstate(const MatchDto& state) {
    std::unique_lock<std::mutex> lck(mtx);
    if (snapshots.isclosed()) {
        return false;
    }

    snapshots.try_push(state);
    return true;
}

// Se podria hacer de forma polimorfica/delegatoria seguro.
MatchDto ControlledPlayer::popstate() { return snapshots.pop(); }


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
    std::unique_lock<std::mutex> lck(mtx);
    if (events.isclosed()) {
        return false;
    }

    events.try_push(dto);
    return true;
}

// Pop lobby info. Bloqueante. Si no hay eventos espera a uno.
lobby_info ControlledPlayer::popinfo() { return events.pop(); }


/// La verdad no deberia pasar no.
// ControlledPlayer::~ControlledPlayer(){
//      disconnect();
// }
