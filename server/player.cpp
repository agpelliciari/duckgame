#include "./player.h"

#include "./gameerror.h"

#include <iostream>
#include <utility>


Player::Player() :_is_open(false) {}

bool Player::operator==(const Player& other) const { return this->ids[0] == other.ids[0] && this->ids[1] == other.ids[1]; }



// Sincronico, al inicio se modifica.
void Player::setplayercount(const uint8_t count){
     if(count > 2 || count <=0){
          throw new GameError("Invalid player count %d ", count);
     }
     this->count = count;
}
uint8_t Player::playercount() const {
     return this->count;
}


// Se sabe is sincronico, solo se modifican mientras no esta abierto.
// Una vez empezado solo se lee. 
void Player::setid(const int ind, player_id id){
     // se podria verificar el indice. Pero no hace falta capaz.
     this->ids[ind] = id;
}

player_id Player::getid(const uint8_t ind) const { return this->ids[ind];}


// Manejo de si esta activo el player. Participando en una partida.

bool Player::open() {
    std::unique_lock<std::mutex> lck(mtx);
    if (_is_open) {
        return false;
    }
    _is_open = true;
    events.reopen();
    return true;
}

bool Player::isopen() {
    std::unique_lock<std::mutex> lck(mtx);
    return _is_open;
}
bool Player::disconnect() {
    std::unique_lock<std::mutex> lck(mtx);
    if (_is_open) {
        _is_open = false;
        events.close();
        return true;
    }
    
    return false;
}

// No hace falta sincronizar/lockear ya que si se llama a este metodo
// La queue sigue abierta. Y no nos importa en todo caso mandar un evento extra o no.
// O eso se dio a
bool Player::recvevent(const Event& event) {
    std::unique_lock<std::mutex> lck(mtx);
    if (_is_open) {
        events.try_push(event);
        return true;
    }
    
    return false;
}

// Se podria hacer de forma polimorfica/delegatoria seguro.
Event Player::popevent() { return events.pop(); }

/// La verdad no deberia pasar no.
//Player::~Player(){
//     disconnect(); 
//}

