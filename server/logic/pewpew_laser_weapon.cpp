

#include "pewpew_laser_weapon.h"

PewPewLaserWeapon::PewPewLaserWeapon(): ammo(12){}

void PewPewLaserWeapon::get_weapon(TypeWeapon& type){
    type = TypeWeapon::PEW_PEW_LASER;
}

bool PewPewLaserWeapon::shoot(ShootingDirection direction,
                               std::vector <PhysicalBullet> &bullets, Tuple bullet_position, PhysicalPlayer &player){

    if (ammo > 0){
        bullets.push_back(PhysicalBullet(bullet_position.x, bullet_position.y, TypeDynamicObject::LASER));
        bullets.push_back(PhysicalBullet(bullet_position.x, bullet_position.y, TypeDynamicObject::LASER));
        bullets.push_back(PhysicalBullet(bullet_position.x, bullet_position.y, TypeDynamicObject::LASER));
        if (direction == ShootingDirection::UP){
            bullets[bullets.size() - 1].shoot_up();
            bullets[bullets.size() - 2].shoot_up();
            bullets[bullets.size() - 3].shoot_up();
            bullets[bullets.size() - 1].add_speed(3, 0);
            bullets[bullets.size() - 2].add_speed(-3, 0);
        } else if (direction == ShootingDirection::LEFT){
            bullets[bullets.size() - 1].shoot_left();
            bullets[bullets.size() - 2].shoot_left();
            bullets[bullets.size() - 3].shoot_left();
            bullets[bullets.size() - 1].add_speed(0, 3);
            bullets[bullets.size() - 2].add_speed(0, -3);
        } else if (direction == ShootingDirection::RIGHT){
            bullets[bullets.size() - 1].shoot_right();
            bullets[bullets.size() - 2].shoot_right();
            bullets[bullets.size() - 3].shoot_right();
            bullets[bullets.size() - 1].add_speed(0, 3);
            bullets[bullets.size() - 2].add_speed(0, -3);
        }
        ammo --;
        return true;
    }
    return false;
}

void PewPewLaserWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::PEW_PEW_LASER;
}

int PewPewLaserWeapon::get_ammo(){
    return ammo;
}
