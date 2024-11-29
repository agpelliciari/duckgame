
#include "ak47_weapon.h"

AK47Weapon::AK47Weapon(): ammo(30), reload_time(15), dispersion_index(0) {}


bool AK47Weapon::shoot(ShootingDirection direction,
                               std::vector <PhysicalBullet> &bullets, Tuple bullet_position,
                       PhysicalPlayer &player, bool &trigger){
    if (ammo > 0){
        if (reload_time > 0){
            reload_time--;
        } else {

            int sign;
            dispersion_index%2 == 0 ? sign = 1 : sign = -1;

            bullets.push_back(PhysicalBullet(bullet_position.x, bullet_position.y));
            if (direction == ShootingDirection::UP){
                player.add_speed(0, -10);
                bullets.back().shoot_up();
                bullets.back().add_speed(dispersion_index * sign, 0);
            } else if (direction == ShootingDirection::LEFT){
                player.add_speed(10, 0);
                player.add_acceleration(-5, 0);
                bullets.back().shoot_left();
                bullets.back().add_speed(0, dispersion_index * sign);
            } else if (direction == ShootingDirection::RIGHT){
                player.add_speed(-10, 0);
                player.add_acceleration(5, 0);
                bullets.back().shoot_right();
                bullets.back().add_speed(0, dispersion_index * sign);
            }
            if (dispersion_index <= 3){
                dispersion_index++;
            } else {
                dispersion_index = 0;
            }
            ammo --;
            reload_time = 15;
            return true;
        }
    }
    return false;
}

void AK47Weapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::AK_47;
}

void AK47Weapon::get_weapon(TypeWeapon& type) {
    type = TypeWeapon::AK_47;
}

int AK47Weapon::get_ammo(){
    return ammo;
}


