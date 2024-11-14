

#include "item.h"

Item::Item(TypeDynamicObject item_, int position_x_, int position_y_,
           int range_x, int range_y, int time_respawn, float time_sleep):
            item(item_), spawn_point{position_x_, position_y_},
            dimension{range_x, range_y}, time_respawn(time_respawn), spawned(true), time_sleep(time_sleep),
            timer(this->time_respawn * this->time_sleep){}

Tuple Item::get_spawn_point() {
    return spawn_point;
}

Tuple Item::get_dimension() {
    return dimension;
}

bool Item::is_spawned() {
    return spawned;
}

void Item::pass_time(){
    if (!spawned && time_respawn > 0) {
        time_respawn--;
    }
    if (time_respawn == 0) {
        spawned = true;
    }
}

void Item::take_item(TypeDynamicObject &item_) {
    item_ = this->item;
    spawned = false;
    timer = this->time_respawn / this->time_sleep;
}

void Item::get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_) {
    position_x_ = this->spawn_point.x;
    position_y_ = this->spawn_point.y;
    object_ = item;
}
