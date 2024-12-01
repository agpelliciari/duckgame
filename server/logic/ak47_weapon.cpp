
#include "ak47_weapon.h"


#define KNOCK_BACK_DURATION 2
#define KNOCK_BACK_MOMENTUM 10

AK47Weapon::AK47Weapon(): ammo(30), reload_time(15), dispersion_index(0), bullet_range(13) {}


SoundEventType AK47Weapon::shoot_sound() const{
    return AK47_SHOT;
}

bool AK47Weapon::shoot(ShootingDirection direction, std::vector <Bullet> &bullets, Tuple bullet_position,
                       PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades){
    if (ammo > 0){
        if (reload_time > 0){
            reload_time--;
        } else {

            int sign;
            dispersion_index%2 == 0 ? sign = 1 : sign = -1;

            bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range, TypeDynamicObject::PROJECTILE, id_player));
            if (direction == ShootingDirection::UP){
                player.add_speed(0, -10);
                bullets.back().shoot_up();
                bullets.back().add_speed(dispersion_index * sign, 0);
            } else if (direction == ShootingDirection::LEFT){
                player.add_impulse_x(KNOCK_BACK_MOMENTUM, KNOCK_BACK_DURATION); // vel_x, duration
                bullets.back().shoot_left();
                bullets.back().add_speed(0, dispersion_index * sign);
            } else if (direction == ShootingDirection::RIGHT){
                player.add_impulse_x(-KNOCK_BACK_MOMENTUM, KNOCK_BACK_DURATION); // vel_x, duration
                bullets.back().shoot_right();
                bullets.back().add_speed(0, dispersion_index * sign);
            }
            if (dispersion_index <= 3){
                dispersion_index++;
            } else {
                dispersion_index = 0;
            }
            player_sounds.push_back(SoundEventType::AK47_SHOT);
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

void AK47Weapon::cheat_ammo(){
    ammo = 99;
}


