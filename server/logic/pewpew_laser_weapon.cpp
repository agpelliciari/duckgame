

#include "pewpew_laser_weapon.h"

PewPewLaserWeapon::PewPewLaserWeapon(): ammo(12), bullet_range(35){}

void PewPewLaserWeapon::get_weapon(TypeWeapon& type){
    type = TypeWeapon::PEW_PEW_LASER;
}

SoundEventType PewPewLaserWeapon::shoot_sound() const{
    return PEWPEW_SHOT;
}


bool PewPewLaserWeapon::shoot(ShootingDirection direction, std::vector <Bullet> &bullets, Tuple bullet_position,
                              PhysicalPlayer &player, bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades){
    trigger = false;
    if (ammo > 0){
        bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range,TypeDynamicObject::LASER, id_player));
        bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range,TypeDynamicObject::LASER, id_player));
        bullets.push_back(Bullet(bullet_position.x, bullet_position.y, bullet_range,TypeDynamicObject::LASER, id_player));
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
        player_sounds.push_back(SoundEventType::PEWPEW_SHOT);
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

void PewPewLaserWeapon::cheat_ammo(){
    ammo = 99;
}
