
#include "box.h"
#include <ctime>
//#include <iostream>

Box::Box(int id, int hp, int x, int y): id(id), spawn_point{x * 16, y * 16}, dimension{16, 16}, spawned(true), life_points(hp) {}

Tuple Box::get_spawn_point() {
    return spawn_point;
}

Tuple Box::get_dimension() {
    return dimension;
}

bool Box::is_spawned() {
    return spawned;
}

void Box::take_damage(){
    if (life_points > 0) {
        life_points--;
        if (life_points <= 0) {
            spawned = false;
        }
    }
}

std::unique_ptr<Weapon> Box::get_item(const int base_mun) {
    std::srand(std::time(nullptr));
    int random_weapon = std::rand() % 9;
    switch (random_weapon){
        case 0:
            return std::make_unique<CowboyPistolWeapon>(base_mun);
        break;
        case 1:
            return std::make_unique<MagnumWeapon>(base_mun);
        break;
        case 2:
            return std::make_unique<DuelPistol>(base_mun);
        break;
        case 3:
            return std::make_unique<PewPewLaserWeapon>(base_mun);
        break;
        case 4:
            return std::make_unique<SniperWeapon>(base_mun);
        break;
        case 5:
            return std::make_unique<ShotgunWeapon>(base_mun);
        break;
        case 6:
            return std::make_unique<AK47Weapon>(base_mun);
        break;
        case 7:
            return std::make_unique<LaserRifleWeapon>(base_mun);
        break;
        case 8:
            return std::make_unique<GrenadeWeapon>(base_mun);
        break;
        default:
            return std::make_unique<CowboyPistolWeapon>(base_mun);
        break;
    }
}

bool Box::destroyed(){
    return life_points <= 0;
}

int Box::get_id() const {
   return id;
}
bool Box::same_id(int id_) {
    return this->id == id_;
}
