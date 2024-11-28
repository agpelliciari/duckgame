
#include "sniper_weapon.h"
#include <ctime>
#include <iostream>

SniperWeapon::SniperWeapon(): ammo(3), charging_time(2),
        init_charging_time(0), final_charging_time(0),charged(true){};

void SniperWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::PEW_PEW_LASER;
}

void SniperWeapon::shoot_sniper(ShootingDirection direction,
                                std::vector <PhysicalBullet> &bullets,
                               Tuple bullet_position){
    bullets.push_back(PhysicalBullet(bullet_position.x, bullet_position.y));
    if (direction == ShootingDirection::UP){
        bullets.back().shoot_up();
    } else if (direction == ShootingDirection::LEFT){
        bullets.back().shoot_left();
    } else if (direction == ShootingDirection::RIGHT){
        bullets.back().shoot_right();
    }
    ammo --;
    charged = false;
}

bool SniperWeapon::shoot(ShootingDirection direction,
                         std::vector<PhysicalBullet> &bullets,
                         Tuple bullet_position, PhysicalPlayer &player) {
    if (ammo <= 0) {
        return false;
    }

    std::time_t current_time = std::time(nullptr);

    if (charged) {
        this->shoot_sniper(direction, bullets, bullet_position);
        init_charging_time = current_time;
        std::cout << "CARGANDO ARMA" << std::endl;
        return true;
    } else {
        if (current_time - init_charging_time >= charging_time) {
            charged = true;
            init_charging_time = 0;
            return this->shoot(direction, bullets, bullet_position, player);
        }
    }
    return false;
}


int SniperWeapon::get_ammo(){
    return ammo;
}

void SniperWeapon::get_weapon(TypeWeapon& type) {
    type = TypeWeapon::SNIPER;
}
