

#include "banana_weapon.h"

BananaWeapon::BananaWeapon(int ammo_):ammo(ammo_){}

void BananaWeapon::get_weapon(TypeWeapon& type) {
    type = TypeWeapon::BANANA;
}


void BananaWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::BANANA;
}

int BananaWeapon::get_ammo(){
    return ammo;
}

void BananaWeapon::cheat_ammo(){
    ammo = 99;
}

bool BananaWeapon::shoot(ShootingDirection direction, std::vector<Bullet> &bullets, Tuple bullet_position,
                   PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds,
                   std::vector<std::unique_ptr<Throwable>> &bananas) {

    trigger = false;
    if (ammo > 0){
        bananas.push_back(std::make_unique<Banana>(bullet_position.x, bullet_position.y, id_player));
        if (direction == ShootingDirection::UP){
            bananas.back()->shoot_up();
        } else if (direction == ShootingDirection::LEFT){
            bananas.back()->shoot_left();
        } else if (direction == ShootingDirection::RIGHT){
            bananas.back()->shoot_right();
        }
        player_sounds.push_back(SoundEventType::GRENADE_THROW);
        ammo --;
        return true;
    }
    return false;

}

SoundEventType BananaWeapon::shoot_sound() const {
    return SoundEventType::BANANA_THROW;
}
