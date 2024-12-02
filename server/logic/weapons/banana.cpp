

#include "banana.h"


Banana::Banana(int init_coord_x, int init_coord_y, int id_player_):
        Throwable(init_coord_x, init_coord_y, TypeDynamicObject::BANANA, id_player_, true){}

void Banana::shoot_right(){
    physical_grenade.shoot_right();
}

void Banana::shoot_left(){
    physical_grenade.shoot_left();
}

void Banana::shoot_up(){
    physical_grenade.shoot_up();
}

bool Banana::exploded(std::vector<Bullet> &bullets, std::vector<MapPoint> &other_objects){

    if (physical_grenade.get_impacted()){
        Tuple position = {0, 0};
        get_pos(position.x, position.y);
        other_objects.push_back(MapPoint{position.x, position.y});
        return true;
    }

    return false;
}





