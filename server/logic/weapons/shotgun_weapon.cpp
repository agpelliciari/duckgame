
#include "shotgun_weapon.h"
#include <ctime>
#include <iostream>

ShotgunWeapon::ShotgunWeapon(int base_ammo): ammo(3* base_ammo), charging_time(2),
        init_charging_time(0), final_charging_time(0), charged(false), bullet_range(7){};

void ShotgunWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::ESCOPETA;
}
SoundEventType ShotgunWeapon::shoot_sound() const{
    return SHOTGUN_SHOT;
}


void ShotgunWeapon::shoot_shotgun(ShootingDirection direction,
                                std::vector <Bullet> &bullets,
                               Tuple bullet_position, int id_player, std::vector<SoundEventType> &player_sounds){
    for (int i = 0; i < 6; i++){
        int sign;
        i%2 == 0 ? sign = 1 : sign = -1;
        int dispersion_index = i * sign;
        bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range, TypeDynamicObject::PROJECTILE, id_player));
        if (direction == ShootingDirection::UP){
            bullets.back().shoot_up();
            bullets.back().add_speed(dispersion_index, -dispersion_index/2);
        } else if (direction == ShootingDirection::LEFT){
            bullets.back().shoot_left();
            bullets.back().add_speed(dispersion_index/2, dispersion_index);
        } else if (direction == ShootingDirection::RIGHT){
            bullets.back().shoot_right();
            bullets.back().add_speed(-dispersion_index/2, dispersion_index);
        }
    }
    player_sounds.push_back(SoundEventType::SHOTGUN_SHOT);
    ammo --;
}

bool ShotgunWeapon::shoot(ShootingDirection direction, std::vector<Bullet> &bullets, Tuple bullet_position,
                          PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<std::unique_ptr<Throwable>> &throwables) {
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
        this->shoot_shotgun(direction, bullets, bullet_position, id_player, player_sounds);
        return true;
    }
    return false;
}

int ShotgunWeapon::get_ammo(){
    return ammo;
}

void ShotgunWeapon::get_weapon(TypeWeapon& type) {
    type = TypeWeapon::ESCOPETA;
}

void ShotgunWeapon::cheat_ammo(){
    ammo = 99;
}
