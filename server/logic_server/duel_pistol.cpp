

#include "duel_pistol.h"

#include <cstdlib>
#include <ctime>

DuelPistol::DuelPistol():ammo(1){}

void DuelPistol::get_weapon(TypeWeapon& type){
    type = TypeWeapon::MAGNUM;
}

void DuelPistol::shoot(ShootingDirection direction,
                               std::vector <PhysicalBullet> &bullets, Tuple bullet_position, PhysicalPlayer &player){

    if (ammo > 0){
        std::srand(std::time(nullptr));
        int dispersion_index = -3 + std::rand() % 7;
        bullets.push_back(PhysicalBullet(bullet_position.x, bullet_position.y));
        if (direction == ShootingDirection::UP){
            bullets.back().shoot_up();
            bullets.back().add_speed(dispersion_index, -dispersion_index);
        } else if (direction == ShootingDirection::LEFT){
            bullets.back().shoot_left();
            bullets.back().add_speed(dispersion_index, dispersion_index);
        } else if (direction == ShootingDirection::RIGHT){
            bullets.back().shoot_right();
            bullets.back().add_speed(-dispersion_index, dispersion_index);
        }
        ammo --;
    }
}


void DuelPistol::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::PISTOLA_DE_DUELOS;
}
