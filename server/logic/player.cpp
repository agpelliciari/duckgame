#include "player.h"

#include <iostream>

Player::Player(int id_, int initial_x, int initial_y, const Configuration& configs):
        id(id_),
        object(initial_x, initial_y, configs),
        is_alive(true),
        helmet(false),
        chest_armor(false),
        move_action(TypeMoveAction::NONE),
        doing_action(),
        aim_up(false),
        life_points(configs.player_health),
        shooting_direction(ShootingDirection::NONE),
        previous_shooting_direction(shooting_direction),
        weapon(nullptr), is_stay_down(false), trigger(false), cheat_weapon_index(0) {}

void Player::get_data(int& id, int& x, int& y, TypeWeapon& weapon_,
                      bool& helmet_equipped, bool& chest_armor_equipped,
                      TypeMoveAction& move_action_, TypeDoingAction &doing_action_,
                      bool &is_alive_, bool &aim_up_, int &life_points_, int &ammo_) {
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
    /*if (doing_action.size() > 0){
        doing_action_ = this->doing_action;
    }*/
    doing_action_ = this->doing_action;
    this->doing_action = TypeDoingAction::NONE;
    is_alive_ = this->is_alive;
    aim_up_ = this->aim_up;
    life_points_ = this->life_points;
    if (weapon != nullptr){
        ammo_ = weapon->get_ammo();
    } else {
        ammo_ = 0;
    }
    //this->doing_action.clear();

}

bool Player::same_id(unsigned int id_) { return id == id_; }

void Player::still() {
    object.stop_moving_x();
}

int Player::get_id() { return id; }

void Player::update(const MatchMap& colition_map, std::vector <Bullet> &bullets, std::vector<Grenade> &grenades) {

    if (is_alive){
        if(object.is_out_of_map()){
            is_alive = false;
        } else {
            if (is_stay_down){
                move_action = TypeMoveAction::STAY_DOWN;
                object.move(colition_map);
            } else {
                object.check_moving_dir(colition_map); // Si esta en vel = 0 pero puede empezar a moverse
                
                object.move(colition_map);
            	object.update_action(move_action);
                this->update_shooting_direction();
                if (trigger){
                    this->shoot(bullets, grenades);
                }
            }
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
        previous_shooting_direction = shooting_direction;
        shooting_direction = ShootingDirection::LEFT;
        return;
    }

    if (move_action == TypeMoveAction::MOVE_RIGHT ||
        move_action == TypeMoveAction::AIR_RIGHT ||
        move_action == TypeMoveAction::FLAP_RIGHT ){
        previous_shooting_direction = shooting_direction;
        shooting_direction = ShootingDirection::RIGHT;
        return;
    }

}

void Player::add_speed(int speed_x, int speed_y) {
    this->object.add_speed(speed_x, speed_y);
}


void Player::change_move_dir(PlayerMovingDir new_dir){
    this->object.change_moving(new_dir);
}

void Player::undo_moving(PlayerMovingDir old_dir){
    this->object.undo_moving(old_dir);
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
    shooting_direction = previous_shooting_direction;
    aim_up = false;
}

bool Player::is_still_alive(){
    return is_alive;
}

void Player::take_damage(int dmg){
    if (is_alive) {
        if (helmet){
            helmet = false;
            player_sounds.push_back(SoundEventType::PLAYER_BROKEN_HELMET);
            return;
        }
        if (chest_armor){
            chest_armor = false;
            player_sounds.push_back(SoundEventType::PLAYER_BROKEN_ARMOR);
            return;
        }

        life_points-=dmg;

        if (life_points <= 0) {
            life_points = 0;
            is_alive = false;
            doing_action=TypeDoingAction::DAMAGED;
            player_sounds.push_back(SoundEventType::PLAYER_DIED);
        } else {
            player_sounds.push_back(SoundEventType::PLAYER_DAMAGED);
        }
    }
}

void Player::shoot(std::vector <Bullet> &bullets, std::vector<Grenade> &grenades){

    if (weapon != nullptr){
        Tuple bullet_position = this->get_map_position();
        Tuple player_dimension = this->get_dimension();

        if (shooting_direction == ShootingDirection::UP){
            bullet_position.x += player_dimension.x / 2;
            bullet_position.y += player_dimension.y  + 5;
        }
        if (shooting_direction == ShootingDirection::LEFT){
            bullet_position.x -= 5;
            bullet_position.y += player_dimension.y / 2;
        }
        if (shooting_direction == ShootingDirection::RIGHT){
            bullet_position.x += player_dimension.x + 5;
            bullet_position.y += player_dimension.y / 2;
        }
        if (weapon->shoot(this->shooting_direction, bullets, bullet_position, this->object, trigger, id, player_sounds, grenades)){
            if (aim_up){
                doing_action=TypeDoingAction::SHOOTING_UP;
            } else {
                doing_action=TypeDoingAction::SHOOTING;
            }
            
            player_sounds.push_back(weapon->shoot_sound());
            
            if(weapon->get_ammo() == 0){
                weapon.reset(); // Reset ! a que se quedo sin balas!
            }
        }

    }
}

void Player::shoot_start(){
    trigger = true;
}

void Player::shoot_end(){
    trigger = false;
}

void Player::equip_helmet(){
    player_sounds.push_back(SoundEventType::PLAYER_EQUIP_HELMET);
    helmet = true;
}

void Player::equip_chest_armor(){
    player_sounds.push_back(SoundEventType::PLAYER_EQUIP_ARMOR);
    chest_armor = true;
}

void Player::stay_down_start(){
    if(object.isOnAir()){
       return;
    }
    
    is_stay_down = true;
    
    move_action = TypeMoveAction::STAY_DOWN;
    object.stay_down_start();
}

void Player::stay_down_end(){
    if(object.isOnAir()){
       return;
    }
    
    is_stay_down = false;
    move_action = TypeMoveAction::NONE;
    object.stay_down_end();
}

bool Player::has_equipment() {
    return (weapon != nullptr);
}

bool Player::pick_up_item(std::vector<SpawnPlace> &spawn_places, std::vector<DroppedItem> &dropped_items){
    Tuple player_position = this->get_map_position();
    Tuple player_dimension = this->get_dimension();

    for (SpawnPlace &spawn_place : spawn_places) {
        if (spawn_place.is_on_range(player_position.x + player_dimension.x / 2,
                                    player_position.y + player_dimension.y / 2)) {
            SpawnActionType action = spawn_place.get_action();
                        
            if(action == SpawnActionType::NO_ACTION){
                continue;
            }
            
            if(action == SpawnActionType::PICKUP_HELMET){
                if(helmet){
                    continue;
                }
                this->equip_helmet();
                spawn_place.get_item(weapon);
                std::cout << "---> PICKUP HELMET?!"<<std::endl;
                return true;
            }
            
            if(action == SpawnActionType::PICKUP_ARMOR){
                if(chest_armor){
                    continue;
                }
                this->equip_chest_armor();  
                spawn_place.get_item(weapon);
                std::cout << "---> PICKUP ARMOR?!"<<std::endl;
                
                return true;
            }
            
            if (weapon == nullptr){
                spawn_place.get_item(weapon);
                doing_action = TypeDoingAction::PICK_UP;
                player_sounds.push_back(SoundEventType::PLAYER_PICKUP);
                std::cout << "---> PICKUP WEAPON?!"<<std::endl;
                return true;
            }
        }
    }
    
    if(weapon != nullptr){
         return false;
    }

    for (DroppedItem &dropped_item : dropped_items) {
        if (dropped_item.is_on_range(player_position.x + player_dimension.x / 2,
                                    player_position.y + player_dimension.y / 2)){
            weapon = dropped_item.get_weapon();
            doing_action = TypeDoingAction::PICK_UP;
            player_sounds.push_back(SoundEventType::PLAYER_PICKUP);
            return true;
        }
    }
    
    return false;
}

void Player::drop_item(std::vector<DroppedItem> &dropped_items){
    if (weapon != nullptr){
        dropped_items.push_back(DroppedItem(std::move(weapon), this->get_map_position().x, this->get_map_position().y, 16, 16));
        player_sounds.push_back(SoundEventType::PLAYER_DROP);
        weapon = nullptr;
    }

}

void Player::jump_start(){
    if(object.jump_start()){
        std::cout<< "WAS JUMP!!!\n";
        player_sounds.push_back(SoundEventType::PLAYER_JUMPED);
        return;
    }
    
    if(object.try_flap_start()){
        std::cout<< "WAS FLAP!!!\n";
        player_sounds.push_back(SoundEventType::PLAYER_FLAP);    
    }
}

void Player::jump_end(){
    object.jump_end();
}

void Player::get_sounds(std::vector<SoundEventType>& sounds){
    for (SoundEventType sound : player_sounds) {
        sounds.push_back(sound);
    }
    player_sounds.clear();
}

void Player::cheat_weapon(int base_mun){
    cheat_weapon_index ++;
    if (cheat_weapon_index > 9){
        cheat_weapon_index = 0;
    }
    switch(cheat_weapon_index){
        case 0:
            weapon = nullptr;
            break;
        case 1:
            weapon = std::make_unique<CowboyPistolWeapon>(base_mun);
            break;
        case 2:
            weapon = std::make_unique<DuelPistol>(base_mun);
            break;
        case 3:
            weapon = std::make_unique<MagnumWeapon>(base_mun);
            break;
        case 4:
            weapon = std::make_unique<ShotgunWeapon>(base_mun);
            break;
        case 5:
            weapon = std::make_unique<SniperWeapon>(base_mun);
            break;
        case 6:
            weapon = std::make_unique<AK47Weapon>(base_mun);
            break;
        case 7:
            weapon = std::make_unique<PewPewLaserWeapon>(base_mun);
            break;
        case 8:
            weapon = std::make_unique<LaserRifleWeapon>(base_mun);
            break;
        case 9:
            weapon = std::make_unique<GrenadeWeapon>(base_mun);
            break;
    }
}

void Player::cheat_armor(){
    helmet = true;
    chest_armor = true;
}

void Player::cheat_ammo(){
    if (weapon != nullptr){
        weapon->cheat_ammo();
    }
}



//Tuple Player::get_position() { return object.get_real_position(); }
