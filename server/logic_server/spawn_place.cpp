

#include "spawn_place.h"

SpawnPlace::SpawnPlace(TypeDynamicObject item_, int position_x_, int position_y_,
           int range_x, int range_y, int time_respawn, float time_sleep):
            item(item_), spawn_point{position_x_, position_y_},
            dimension{range_x, range_y}, time_respawn(time_respawn), spawned(true), time_sleep(time_sleep),
            timer(this->time_respawn * this->time_sleep){
    possible_weapons.reserve(1);
            }

void SpawnPlace::spawn_item() {

    possible_weapons.reserve(1);
    possible_weapons.clear();
    // TODO modificar para que aparezcan armas al azar
    possible_weapons.emplace_back(std::make_unique<CowboyPistolWeapon>());
    spawned = true;
}

std::unique_ptr<Weapon> SpawnPlace::get_weapon(){
    if (spawned){
        spawned = false;
        timer = this->time_respawn / this->time_sleep;
        auto weapon = std::move(possible_weapons.back());
        possible_weapons.pop_back();
        return weapon;
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
        time_respawn--;
    }
    if (time_respawn == 0) {
        this->spawn_item();
    }
}

void SpawnPlace::take_item(TypeDynamicObject &item_) {
    item_ = this->item;
    spawned = false;
    timer = this->time_respawn / this->time_sleep;
}

void SpawnPlace::get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_) {
    position_x_ = this->spawn_point.x;
    position_y_ = this->spawn_point.y;
    if (!possible_weapons.empty()){
        object_ = item;
    }
}

bool SpawnPlace::is_on_range(int player_position_x, int player_position_y){
    return (player_position_x >= spawn_point.x && player_position_x <= spawn_point.x + dimension.x &&
                player_position_y >= spawn_point.y && player_position_y <= spawn_point.x + dimension.y);
}