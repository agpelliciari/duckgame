#include "./player.h"

#include <iostream>
#include <utility>


Player::Player(player_id ide): id(ide) { _is_open = true; }

bool Player::operator==(const Player& other) const { return this->id == other.id; }


// El lock es por si algun thread esta en el medio de disconnect...
bool Player::isopen() {
    std::unique_lock<std::mutex> lck(mtx);
    return _is_open;
}
void Player::close() { events.close(); }

bool Player::disconnect() {
    std::unique_lock<std::mutex> lck(mtx);
    if (_is_open) {
        _is_open = false;
        return true;
    }

    return false;
}
player_id Player::getid() const { return this->id; }


// No hace falta sincronizar/lockear ya que si se llama a este metodo
// La queue sigue abierta. Y no nos importa en todo caso mandar un evento extra o no.
// O eso se dio a
void Player::recvevent(const Event& event) {
    if (_is_open) {
        events.try_push(event);
    }
}

// Se podria hacer de forma polimorfica/delegatoria seguro.
Event Player::popevent() { return events.pop(); }
