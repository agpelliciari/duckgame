

#include "spawn_place.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

SpawnPlace::SpawnPlace(int position_x_, int position_y_,
           int range_x, int range_y, int time_respawn, float time_sleep, int seed_):
            possible_weapon(nullptr), possible_helmet(false), possible_armor(false), spawn_point{position_x_, position_y_},
            dimension{range_x, range_y}, time_respawn(time_respawn), spawned(false), time_sleep(time_sleep),
            timer(this->time_respawn * this->time_sleep), seed(seed_){

            }

void SpawnPlace::spawn_item() {
    // TODO refactorizar este switch
    if (spawned) {
        return;
    }
    auto start_time = std::chrono::high_resolution_clock::now();
    //std::srand(std::time(nullptr) + seed);
    //int random_weapon = std::rand() % 11;
    int random_weapon = 10;
    switch (random_weapon){
        case 0:
            possible_weapon = std::make_unique<CowboyPistolWeapon>();
            spawned = true;
            break;
        case 1:
            possible_weapon = std::make_unique<MagnumWeapon>();
            spawned = true;
            break;
        case 2:
            possible_weapon = std::make_unique<DuelPistol>();
            spawned = true;
            break;
        case 3:
            possible_weapon = std::make_unique<PewPewLaserWeapon>();
            spawned = true;
            break;
        case 4:
            possible_weapon = std::make_unique<SniperWeapon>();
            spawned = true;
            break;
        case 5:
            possible_weapon = std::make_unique<ShotgunWeapon>();
            spawned = true;
            break;
        case 6:
            possible_weapon = std::make_unique<AK47Weapon>();
            spawned = true;
            break;
        case 7:
            possible_weapon = std::make_unique<LaserRifleWeapon>();
            spawned = true;
            break;

        case 8:
            possible_helmet = true;
            std::cout<<"HELMET SPAWNED"<<std::endl;
            spawned = true;
            break;
        case 9:
            possible_armor = true;
            std::cout<<"CHEST ARMOR SPAWNED"<<std::endl;
            spawned = true;
            break;
        case 10:
            possible_weapon = std::make_unique<GrenadeWeapon>();
            spawned = true;
            break;

        default:
            possible_weapon = std::make_unique<CowboyPistolWeapon>();
            spawned = true;
            break;
    }
}

std::unique_ptr<Weapon> SpawnPlace::get_weapon(bool &helmet, bool &armor){
    if (spawned){
        spawned = false;
        timer = 200;
        if (possible_helmet && helmet == false) {
            helmet = true;
            possible_helmet = false;
            return nullptr;
        }
        if (possible_armor && armor == false) {
            armor = true;
            possible_armor = false;
            return nullptr;
        }
        if (possible_weapon != nullptr) {
            auto weapon = std::move(possible_weapon);
            possible_weapon = nullptr;
            return weapon;
        }
    }
    return nullptr;
}

Tuple SpawnPlace::get_spawn_point() {
    return spawn_point;
}

Tuple SpawnPlace::get_dimension() {
    return dimension;
}

bool SpawnPlace::is_spawned() {
    return spawned;
}



void SpawnPlace::pass_time(){
    if (!spawned && time_respawn > 0) {
        timer--;
        //std::cout << "TIMER SPAWNER: "<< timer <<std::endl;
        if (timer <= 0) {
            this->spawn_item();
        }
    }

}

void SpawnPlace::take_item(TypeDynamicObject &item_) {

    spawned = false;
    timer = this->time_respawn / this->time_sleep;
    if (possible_helmet){
        item_ = TypeDynamicObject::HELMET;

        return;
    }
    if (possible_armor){
        item_ = TypeDynamicObject::ARMOR;

        return;
    }
    item_ = this->item;

}

void SpawnPlace::get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_) {
    position_x_ = this->spawn_point.x;
    position_y_ = this->spawn_point.y + 10;
    if (possible_helmet){
        object_ = TypeDynamicObject::HELMET;
        return;
    }
    if (possible_armor){
        object_ = TypeDynamicObject::ARMOR;
        return;
    }
    if (possible_weapon != nullptr){
        possible_weapon->get_type(object_);
    }
}

bool SpawnPlace::is_on_range(int player_position_x, int player_position_y){
    return (player_position_x >= spawn_point.x - 24 && player_position_x <= spawn_point.x + dimension.x  + 24&&
                player_position_y >= spawn_point.y-24 && player_position_y <= spawn_point.y + dimension.y+24);
}


TypeDynamicObject SpawnPlace::get_item(){
    if (possible_helmet){
        return TypeDynamicObject::HELMET;
    }
    if (possible_armor){
        return TypeDynamicObject::ARMOR;
    }

    return item;
}
