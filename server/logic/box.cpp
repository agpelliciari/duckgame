
#include "box.h"

Box::Box(int id, int x, int y): id(id), spawn_point{x * 16, y * 16}, dimension{16, 16}, spawned(true), life_points(2) {
    possible_rewards = {
        //TypeDynamicObject::HELMET,
        //TypeDynamicObject::ARMOR,
        //TypeDynamicObject::MAGNUM,
        TypeDynamicObject::PISTOLA_COWBOY,
        //TypeDynamicObject::PEW_PEW_LASER
    };
}

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

TypeDynamicObject Box::get_item() {
    std::srand(std::time(nullptr));
    int reward_index = 0 + std::rand() % possible_rewards.size();
    return possible_rewards[reward_index];
}

bool Box::destroyed(){
    return life_points <= 0;
}

bool Box::same_id(int id_) {
    return this->id == id_;
}
