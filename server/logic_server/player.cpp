
#include "player.h"

Player::Player(int id, int initial_x, int initial_y):
        id(id),
        is_alive(true),
        coordinates(initial_x, initial_y),
        weapon(),
        helmet(),
        chest_armor(),
        move_action() {}

void Player::get_data(const int& id, const int& x, const int& y, const TypeWeapon& weapon,
                      const bool& helmet_equipped, const bool& chest_armor_equipped,
                      const TypeMoveAction& move_action) {
    id = this->id;
    this->coordinates.get_coordinates(x, y);
    this->weapon.get_weapon(weapon);
    this->helmet.is_equipped(helmet_equipped);
    this->chest_armor.is_equipped(chest_armor_equipped);
    this->move_action.get_move_action(move_action);
}

bool Player::same_id(int id) { return this->id == id; }

void Player::still() { move_action.still(); }

void Player::move_right() {
    coordinates.move_right();
    move_action.move_right();
}

void Player::move_left() {
    coordinates.move_left();
    move_action.move_left();
}

void Player::stay_down() { move_action.stay_down(); }

void Player::jump() {
    move_action.jump();
    coordinates.jump();
}
