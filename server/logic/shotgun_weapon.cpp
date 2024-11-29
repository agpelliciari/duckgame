
#include "shotgun_weapon.h"
#include <ctime>
#include <iostream>

ShotgunWeapon::ShotgunWeapon(): ammo(3), charging_time(2),
        init_charging_time(0), final_charging_time(0), charged(false){};

void ShotgunWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::ESCOPETA;
}

void ShotgunWeapon::shoot_shotgun(ShootingDirection direction,
                                std::vector <PhysicalBullet> &bullets,
                               Tuple bullet_position){
    for (int i = 0; i < 6; i++){
        int sign;
        i%2 == 0 ? sign = 1 : sign = -1;
        int dispersion_index = i * sign;
        bullets.push_back(PhysicalBullet(bullet_position.x, bullet_position.y));
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
    ammo --;
}

bool ShotgunWeapon::shoot(ShootingDirection direction,
                         std::vector<PhysicalBullet> &bullets,
                         Tuple bullet_position, PhysicalPlayer &player) {

    if (ammo <= 0) {
        return false;
    }

    std::time_t current_time = std::time(nullptr);


    if (init_charging_time == 0) {
        init_charging_time = current_time;
        std::cout << "CARGANDO ARMA" << std::endl;
        return false;
    }
    if (current_time - init_charging_time >= charging_time) {
        init_charging_time = 0;
        this->shoot_shotgun(direction, bullets, bullet_position);
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
