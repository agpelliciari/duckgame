#include "player.h"

#include <iostream>

Player::Player(int id_, int initial_x, int initial_y):
        id(id_),
        object(initial_x, initial_y),
        is_alive(true),
        helmet(false),
        chest_armor(false),
        move_action(TypeMoveAction::NONE),
        doing_action(),
        aim_up(false),
        life_points(3),
        shooting_direction(ShootingDirection::NONE),
        weapon(nullptr){}

void Player::get_data(int& id, int& x, int& y, TypeWeapon& weapon_,
                      bool& helmet_equipped, bool& chest_armor_equipped,
                      TypeMoveAction& move_action_, std::vector<SoundEventType>& sounds,
                      bool &is_alive_, bool &aim_up_) {
    id = this->id;
    this->object.get_real_position(x, y);

    if (this->weapon != nullptr){
        this->weapon->get_weapon(weapon_);
    }

    helmet_equipped = this->helmet;
    chest_armor_equipped = this->chest_armor;

    //this->weapon.get_weapon(weapon);
    //this->helmet.is_equipped(helmet_equipped);
    //this->chest_armor.is_equipped(chest_armor_equipped);
    move_action_ = this->move_action;
    if (this->doing_action.size() > 0){
        sounds.push_back(PLAYER_JUMPED);
        this->doing_action.clear();
    }
    is_alive_ = this->is_alive;
    aim_up_ = this->aim_up;

}

bool Player::same_id(unsigned int id_) { return id == id_; }

void Player::still() {
    object.stop_moving_x();
}

int Player::get_id() { return id; }

void Player::update(const MatchMap& colition_map) {
    if (is_alive){
        if(object.is_out_of_map()){
            is_alive = false;
        } else {
            object.move(colition_map);
            object.update_action(move_action);
            this->update_shooting_direction();
        }
    } else {
        this->stay_down_start();
    }

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

bool Player::is_still_alive(){
    return is_alive;
}

void Player::take_damage(){
    if (is_alive) {
        if (helmet){
            helmet = false;
            return;
        }
        if (chest_armor){
            chest_armor = false;
            return;
        }

        life_points--;
        doing_action.push_back(TypeDoingAction::DAMAGED);
        if (life_points == 0) {
            is_alive = false;
        }
    }
}

void Player::shoot(std::vector <PhysicalBullet> &bullets){
    if (weapon != nullptr){
        Tuple bullet_position = this->get_map_position();
        Tuple player_dimension = this->get_dimension();
        if (shooting_direction == ShootingDirection::UP){
            doing_action.push_back(TypeDoingAction::SHOOTING_UP);
            bullet_position.x += player_dimension.x / 2;
            bullet_position.y += player_dimension.y  + 5;
        }
        if (shooting_direction == ShootingDirection::LEFT){
            doing_action.push_back(TypeDoingAction::SHOOTING);
            bullet_position.x -= 5;
            bullet_position.y += player_dimension.y / 2;
        }
        if (shooting_direction == ShootingDirection::RIGHT){
            doing_action.push_back(TypeDoingAction::SHOOTING);
            bullet_position.x += player_dimension.x + 5;
            bullet_position.y += player_dimension.y / 2;
        }
        weapon->shoot(this->shooting_direction, bullets, bullet_position, this->object);
    }
}

void Player::stay_down_start(){
    move_action = TypeMoveAction::STAY_DOWN;
    object.stay_down_start();
}

void Player::stay_down_end(){
    move_action = TypeMoveAction::NONE;
    object.stay_down_end();
}

void Player::pick_up_item(std::vector<SpawnPlace> &spawn_places, std::vector<DroppedItem> &dropped_items){
    doing_action.push_back(TypeDoingAction::PICK_UP);
    if (weapon != nullptr){
        return;
    }
    Tuple player_position = this->get_map_position();
    Tuple player_dimension = this->get_dimension();

    for (SpawnPlace &spawn_place : spawn_places) {
        if (spawn_place.is_on_range(player_position.x + player_dimension.x / 2,
                                    player_position.y + player_dimension.y / 2)) {
            weapon = spawn_place.get_weapon();
            return;
        }
    }

    for (DroppedItem &dropped_item : dropped_items) {
        if (dropped_item.is_on_range(player_position.x + player_dimension.x / 2,
                                    player_position.y + player_dimension.y / 2)){
            weapon = dropped_item.get_weapon();
            return;
        }
    }
}

void Player::drop_item(std::vector<DroppedItem> &dropped_items){
    if (weapon != nullptr){
        dropped_items.push_back(DroppedItem(std::move(weapon), this->get_map_position().x, this->get_map_position().y, 16, 16));
        weapon = nullptr;
    }

}

void Player::jump_start(){
    object.jump_start();
}

void Player::jump_end(){
    object.jump_end();
}

//Tuple Player::get_position() { return object.get_real_position(); }
