
#include "laser_rifle_weapon.h"
#include <ctime>

LaserRifleWeapon::LaserRifleWeapon(): ammo(10), reload_time(15), bullet_range(30),
        dispersion_factor(5), last_shoot_time(0){}

void LaserRifleWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::LASER_RIFLE;
}


SoundEventType LaserRifleWeapon::shoot_sound() const{
    return LASER_SHOT ;
}

void LaserRifleWeapon::get_weapon(TypeWeapon& type) {
    type = TypeWeapon::LASER_RIFLE;
}

int LaserRifleWeapon::get_ammo(){
    return ammo;
}


bool LaserRifleWeapon::shoot(ShootingDirection direction, std::vector <Bullet> &bullets, Tuple bullet_position,
                       PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades){
    if (ammo > 0){
        if (reload_time > 0){
            reload_time--;
        } else {

            std::time_t current_time = std::time(nullptr);

            if (current_time - last_shoot_time <= 2){
                if (dispersion_factor >= 0){
                    dispersion_factor--;
                }
            } else {
                dispersion_factor = 5;
            }

            bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range, TypeDynamicObject::LASER, id_player, true));
            if (direction == ShootingDirection::UP){
                bullets.back().shoot_up();
            } else if (direction == ShootingDirection::LEFT){
                bullets.back().shoot_left();
                bullets.back().add_speed(0, -dispersion_factor);
            } else if (direction == ShootingDirection::RIGHT){
                bullets.back().shoot_right();
                bullets.back().add_speed(0, -dispersion_factor);
            }
            player_sounds.push_back(SoundEventType::LASER_SHOT);
            ammo --;
            reload_time = 15;
            last_shoot_time = current_time;
            return true;
        }
    }
    return false;
}
