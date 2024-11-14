#include "player.h"

#include <iostream>

Player::Player(int id_, int initial_x, int initial_y):
        id(id_),
        object(initial_x, initial_y),
        is_alive(true),
        helmet(),
        chest_armor(),
        move_action(TypeMoveAction::NONE),
        aim_up(false),
        life_points(5),
        shooting_direction(ShootingDirection::NONE),
        weapon(){}

void Player::get_data(int& id, int& x, int& y, TypeWeapon& weapon_,
                      const bool& helmet_equipped, const bool& chest_armor_equipped,
                      TypeMoveAction& move_action_) {
    id = this->id;
    this->object.get_real_position(x, y);

    //if (this->weapon != nullptr){
        this->weapon.get_weapon(weapon_);
    //}

    //this->weapon.get_weapon(weapon);
    this->helmet.is_equipped(helmet_equipped);
    this->chest_armor.is_equipped(chest_armor_equipped);
    move_action_ = this->move_action;
}

bool Player::same_id(unsigned int id_) { return id == id_; }

void Player::still() {
    object.stop_moving_x();
}

int Player::get_id() { return id; }

void Player::update(const MatchMap& colition_map) {
    object.move(colition_map);
    object.update_action(move_action);
    this->update_shooting_direction();
}

void Player::update_shooting_direction(){
    if (aim_up) {
        shooting_direction = ShootingDirection::UP;
        return;
    }

    if (move_action == TypeMoveAction::MOVE_LEFT ||
        move_action == TypeMoveAction::AIR_LEFT ||
        move_action == TypeMoveAction::FLAP_LEFT) {
        shooting_direction = ShootingDirection::LEFT;
        return;
    }

    if (move_action == TypeMoveAction::MOVE_RIGHT ||
        move_action == TypeMoveAction::AIR_RIGHT ||
        move_action == TypeMoveAction::FLAP_RIGHT ){
        shooting_direction = ShootingDirection::RIGHT;
        return;
    }

}

void Player::add_speed(int speed_x, int speed_y) {
    this->object.add_speed(speed_x, speed_y);
}

Tuple Player::get_map_position(){
    return object.get_position();
}

Tuple Player::get_dimension(){
    return object.get_dimension();
}

void Player::stop_moving_x(){
    object.stop_moving_x();
}

void Player::aim_up_start(){
    aim_up = true;
}
void Player::aim_up_end(){
    aim_up = false;
}

void Player::take_damage(){
    if (is_alive) {
        life_points--;
        if (life_points == 0) {
            is_alive = false;
        }
    }
}

void Player::shoot(std::vector <PhysicalBullet> &bullets){
    //if (weapon != nullptr){
        Tuple bullet_position = this->get_map_position();
        Tuple player_dimension = this->get_dimension();
        bullet_position.x += player_dimension.x / 2;
        bullet_position.y += player_dimension.y / 2;
        weapon.shoot(this->shooting_direction, bullets, bullet_position);
    //}
}

//Tuple Player::get_position() { return object.get_real_position(); }
