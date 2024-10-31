#include "./controlledplayer.h"

#include <iostream>
#include <sstream>
#include <utility>

#include "./gameerror.h"

ControlledPlayer::ControlledPlayer(player_id first): _is_open(false), count(1), ids() {
    ids[0] = first;
    ids[1] = first;
}

ControlledPlayer::ControlledPlayer(player_id first, player_id second):
        _is_open(false), count(2), ids() {
    ids[0] = first;
    ids[1] = second;
}


/*
// Maximo dos asi que no hace falta algo general.
ControlledPlayer::ControlledPlayer(uint8_t count): _is_open(false), count(0), ids() {
    if (count > 2 || count == 0) {
        throw new GameError("Invalid player count %d ", count);
    }
    this->count = count;
}
*/

bool ControlledPlayer::operator==(const ControlledPlayer& other) const {
    return this->ids[0] == other.ids[0] && this->ids[1] == other.ids[1];
}

uint8_t ControlledPlayer::playercount() const { return this->count; }


player_id ControlledPlayer::getid(const uint8_t ind) const { return this->ids[ind]; }


// Manejo de si esta activo el player. Participando en una partida.

bool ControlledPlayer::open() {
    std::unique_lock<std::mutex> lck(mtx);
    if (_is_open) {
        return false;
    }
    _is_open = true;
    snapshots.reopen();
    return true;
}

bool ControlledPlayer::isopen() {
    std::unique_lock<std::mutex> lck(mtx);
    return _is_open;
}
bool ControlledPlayer::disconnect() {
    std::unique_lock<std::mutex> lck(mtx);
    if (_is_open) {
        _is_open = false;
        snapshots.close();
        // std::cout << "CLOSED EVENTS FOR "<< (int)getid(0)<< std::endl;
        return true;
    }

    return false;
}

// No hace falta sincronizar/lockear ya que si se llama a este metodo
// La queue sigue abierta. Y no nos importa en todo caso mandar un evento extra o no.
// O eso se dio a
bool ControlledPlayer::recvstate(const MatchDto& state) {
    std::unique_lock<std::mutex> lck(mtx);
    if (_is_open) {
        snapshots.try_push(state);
        return true;
    }

    return false;
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

/// La verdad no deberia pasar no.
// ControlledPlayer::~ControlledPlayer(){
//      disconnect();
// }
