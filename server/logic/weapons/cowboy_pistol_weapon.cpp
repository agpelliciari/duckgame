

#include "cowboy_pistol_weapon.h"

CowboyPistolWeapon::CowboyPistolWeapon(int base_ammo): ammo(6*base_ammo), bullet_range(20){}

void CowboyPistolWeapon::get_weapon(TypeWeapon& type){
    type = TypeWeapon::PISTOLA_COWBOY;
}

SoundEventType CowboyPistolWeapon::shoot_sound() const{
    return COWBOY_SHOT;
}


bool CowboyPistolWeapon::shoot(ShootingDirection direction, std::vector <Bullet> &bullets,
                               Tuple bullet_position, PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<std::unique_ptr<Throwable>> &throwables){
    trigger = false;
    if (ammo > 0){
        bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range, TypeDynamicObject::PROJECTILE, id_player));
        if (direction == ShootingDirection::UP){
            bullets.back().shoot_up();
        } else if (direction == ShootingDirection::LEFT){
            bullets.back().shoot_left();
        } else if (direction == ShootingDirection::RIGHT){
            bullets.back().shoot_right();
        }
        player_sounds.push_back(SoundEventType::COWBOY_SHOT);
        ammo --;
        return true;

    }
    return false;

}

void CowboyPistolWeapon::get_type(TypeDynamicObject &type){
    type = TypeDynamicObject::PISTOLA_COWBOY;
}

int CowboyPistolWeapon::get_ammo(){
    return ammo;
}

void CowboyPistolWeapon::cheat_ammo(){
    ammo = 99;
}
