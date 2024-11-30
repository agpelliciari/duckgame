
#include "box.h"
#include <ctime>

Box::Box(int id, int x, int y): id(id), spawn_point{x * 16, y * 16}, dimension{16, 16}, spawned(true), life_points(2) {}

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

std::unique_ptr<Weapon> Box::get_item() {
    std::srand(std::time(nullptr));
    int random_weapon = std::rand() % 8;
    switch (random_weapon){
        case 0:
            return std::make_unique<CowboyPistolWeapon>();
        break;
        case 1:
            return std::make_unique<MagnumWeapon>();
        break;
        case 2:
            return std::make_unique<DuelPistol>();
        break;
        case 3:
            return std::make_unique<PewPewLaserWeapon>();
        break;
        case 4:
            return std::make_unique<SniperWeapon>();
        break;
        case 5:
            return std::make_unique<ShotgunWeapon>();
        break;
        case 6:
            return std::make_unique<AK47Weapon>();
        break;
        case 7:
            return std::make_unique<LaserRifleWeapon>();
        break;
        default:
            return std::make_unique<CowboyPistolWeapon>();
        break;
    }
}

bool Box::destroyed(){
    return life_points <= 0;
}

bool Box::same_id(int id_) {
    return this->id == id_;
}
