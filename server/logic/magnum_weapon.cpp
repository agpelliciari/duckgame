
//incluyo estas librerias provisorias
#include <cstdlib>
#include <ctime>

#include "magnum_weapon.h"

MagnumWeapon::MagnumWeapon(): ammo(6), bullet_range(20){}

void MagnumWeapon::get_weapon(TypeWeapon& type){
    type = TypeWeapon::MAGNUM;
}

bool MagnumWeapon::shoot(ShootingDirection direction, std::vector <Bullet> &bullets, Tuple bullet_position,
                         PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades){
    trigger = false;
    if (ammo > 0){
        std::srand(std::time(nullptr));
        int dispersion_index = -2 + std::rand() % 5;
        bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range, TypeDynamicObject::PROJECTILE, id_player));
        if (direction == ShootingDirection::UP){
            player.add_speed(0, -20);
            bullets.back().shoot_up();
            bullets.back().add_speed(dispersion_index, -dispersion_index);
        } else if (direction == ShootingDirection::LEFT){
            player.add_speed(20, 0);
            player.add_acceleration(-5, 0);
            bullets.back().shoot_left();
            bullets.back().add_speed(dispersion_index, dispersion_index);
        } else if (direction == ShootingDirection::RIGHT){
            player.add_speed(-20, 0);
            player.add_acceleration(5, 0);
            bullets.back().shoot_right();
            bullets.back().add_speed(-dispersion_index, dispersion_index);
        }
        ammo --;
        return true;
        player_sounds.push_back(SoundEventType::MAGNUM_SHOT);
    }
    return false;
}

void MagnumWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::MAGNUM;
}

int MagnumWeapon::get_ammo(){
    return ammo;
}
