#include "player.h"

#include <iostream>

Player::Player(unsigned int id_, int initial_x, int initial_y):
        id(id_),
        object(initial_x, initial_y, 30, 10, 0, 0, 10),
        is_alive(true),
        weapon(),
        helmet(),
        chest_armor(),
        move_action() {}

void Player::get_data(int& id, int& x, int& y, const TypeWeapon& weapon,
                      const bool& helmet_equipped, const bool& chest_armor_equipped,
                      TypeMoveAction& move_action) {
    id = this->id;
    this->object.get_position(x, y);
    this->weapon.get_weapon(weapon);
    this->helmet.is_equipped(helmet_equipped);
    this->chest_armor.is_equipped(chest_armor_equipped);
    this->move_action.get_move_action(move_action);
}

bool Player::same_id(unsigned int id_) { return id == id_; }

void Player::still() {
    move_action.still();
}

void Player::update_position(){
    object.move();
}

void Player::add_speed(int speed_x, int speed_y){
    this->object.add_speed(speed_x, speed_y);
}
