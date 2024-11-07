#include "player.h"

#include <iostream>

Player::Player(unsigned int id_, int initial_x, int initial_y):
        id(id_),
        object(initial_x, initial_y, 10, 30, 0, 0, 10),
        is_alive(true),
        weapon(),
        helmet(),
        chest_armor(),
        move_action(TypeMoveAction::NONE) {}

void Player::get_data(int& id, int& x, int& y, const TypeWeapon& weapon,
                      const bool& helmet_equipped, const bool& chest_armor_equipped,
                      TypeMoveAction& move_action_) {
    id = this->id;
    this->object.get_position(x, y);
    this->weapon.get_weapon(weapon);
    this->helmet.is_equipped(helmet_equipped);
    this->chest_armor.is_equipped(chest_armor_equipped);
    move_action_ = this->move_action;
}

bool Player::same_id(unsigned int id_) { return id == id_; }

void Player::still() {
    // move_action.still();
    object.stop_moving_x();
}

void Player::update(const MatchMap& colition_map) {
    object.move(colition_map);
    object.update_action(move_action);
}

void Player::add_speed(int speed_x, int speed_y) { this->object.add_speed(speed_x, speed_y); }

PhysicalObject& Player::get_object(){
    return this->object;
}

Tuple Player::get_map_position(){
    return object.get_position();
}

Tuple Player::get_dimension(){
    return object.get_dimension();
}

Tuple Player::get_position() { return object.get_real_position(); }
