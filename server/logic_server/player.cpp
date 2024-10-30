#include "player.h"

#include <iostream>

Player::Player(unsigned int id_, int initial_x, int initial_y):
        id(id_),
        coordinates(initial_x, initial_y),
        is_alive(true),
        weapon(),
        helmet(),
        chest_armor(),
        move_action() {}

void Player::get_data(int& id, int& x, int& y, const TypeWeapon& weapon,
                      const bool& helmet_equipped, const bool& chest_armor_equipped,
                      const TypeMoveAction& move_action) {
    id = this->id;
    this->coordinates.get_coordinates(x, y);
    this->weapon.get_weapon(weapon);
    this->helmet.is_equipped(helmet_equipped);
    this->chest_armor.is_equipped(chest_armor_equipped);
    this->move_action.get_move_action(move_action);
}

bool Player::same_id(unsigned int id_) { return id == id_; }

void Player::still() {
    move_action.still();
    //coordinates.update_position_y();
}

void Player::move_right() {
    coordinates.move_right();
    move_action.move_right();
    //coordinates.update_position_y();
}

void Player::move_left() {
    coordinates.move_left();
    move_action.move_left();
    //coordinates.update_position_y();
}

void Player::stay_down() {
    move_action.stay_down();
    //coordinates.update_position_y();
}

void Player::jump() {
    move_action.jump();
    coordinates.jump();
}

void Player::update_position_y(){
    coordinates.update_position_y();
}
