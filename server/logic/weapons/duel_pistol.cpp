

#include "duel_pistol.h"

#include <cstdlib>
#include <ctime>

DuelPistol::DuelPistol(int base_ammo):ammo(base_ammo), bullet_range(5){}

void DuelPistol::get_weapon(TypeWeapon& type){
    type = TypeWeapon::MAGNUM;
}

SoundEventType DuelPistol::shoot_sound() const{
    return DUEL_PISTOL_SHOT;
}



bool DuelPistol::shoot(ShootingDirection direction, std::vector <Bullet> &bullets, Tuple bullet_position,
                       PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<std::unique_ptr<Throwable>> &throwables){
    trigger = false;
    if (ammo > 0){
        std::srand(std::time(nullptr));
        int dispersion_index = -3 + std::rand() % 7;
        bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range, TypeDynamicObject::PROJECTILE, id_player));
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
        player_sounds.push_back(SoundEventType::DUEL_PISTOL_SHOT);
        ammo --;
        return true;
    }
    return false;
}


void DuelPistol::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::PISTOLA_DE_DUELOS;
}

int DuelPistol::get_ammo(){
    return ammo;
}

void DuelPistol::cheat_ammo(){
    ammo = 99;
}
