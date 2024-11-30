
#include "sniper_weapon.h"
#include <ctime>
#include <iostream>

SniperWeapon::SniperWeapon(): ammo(2), charging_time(2),
        init_charging_time(0), final_charging_time(0),charged(false), bullet_range(64){};

void SniperWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::SNIPER;
}

void SniperWeapon::shoot_sniper(ShootingDirection direction, std::vector<Bullet> &bullets,
                               Tuple bullet_position, int id_player, std::vector<SoundEventType> &player_sounds){
    bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range, TypeDynamicObject::PROJECTILE, id_player));

    if (direction == ShootingDirection::UP){
        bullets.back().shoot_up();
    } else if (direction == ShootingDirection::LEFT){
        bullets.back().shoot_left();
    } else if (direction == ShootingDirection::RIGHT){
        bullets.back().shoot_right();
    }
    player_sounds.push_back(SoundEventType::SNIPER_SHOT);
    ammo --;
    charged = false;
}

bool SniperWeapon::shoot(ShootingDirection direction, std::vector<Bullet> &bullets, Tuple bullet_position,
                         PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades) {
    trigger = false;
    if (ammo <= 0) {
        return false;
    }

    std::time_t current_time = std::time(nullptr);


    if (init_charging_time == 0) {
        init_charging_time = current_time;
        player_sounds.push_back(SoundEventType::PLAYER_RELOADING);
        return false;
    }
    if (current_time - init_charging_time >= charging_time) {
       init_charging_time = 0;
       this->shoot_sniper(direction, bullets, bullet_position, id_player, player_sounds);
       return true;
    }
    return false;
}



int SniperWeapon::get_ammo(){
    return ammo;
}

void SniperWeapon::get_weapon(TypeWeapon& type) {
    type = TypeWeapon::SNIPER;
}
