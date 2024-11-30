#include <ctime>
#include "grenade_weapon.h"

GrenadeWeapon::GrenadeWeapon():ammo(1){}

void GrenadeWeapon::get_weapon(TypeWeapon& type){
    type = TypeWeapon::GRANADA;
}

void GrenadeWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::GRANADA;
}

int GrenadeWeapon::get_ammo(){
    return ammo;
}

bool GrenadeWeapon::shoot(ShootingDirection direction,
                   std::vector<Bullet> &bullets, Tuple bullet_position, PhysicalPlayer &player,
                   bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades){

    trigger = false;
    if (ammo > 0){
        grenades.push_back(Grenade(bullet_position.x, bullet_position.y, TypeDynamicObject::GRANADA, id_player, std::time(nullptr)));
        if (direction == ShootingDirection::UP){
            grenades.back().shoot_up();
        } else if (direction == ShootingDirection::LEFT){
            grenades.back().shoot_left();
        } else if (direction == ShootingDirection::RIGHT){
            grenades.back().shoot_right();
        }
        player_sounds.push_back(SoundEventType::GRENADE_THROW);
        ammo --;
        return true;
    }



    return false;

}
