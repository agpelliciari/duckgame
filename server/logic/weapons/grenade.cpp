

#include "grenade.h"
#include <ctime>

Grenade::Grenade(int init_coord_x, int init_coord_y, int id_player_, int time):
        Throwable(init_coord_x, init_coord_y, TypeDynamicObject::GRANADA, id_player_, false),
        detonation_time(4), shoot_time(time){}

void Grenade::shoot_right(){
    std::time_t current_time = std::time(nullptr);
    current_time = shoot_time;
    physical_grenade.shoot_right();
}

void Grenade::shoot_left(){
    std::time_t current_time = std::time(nullptr);
    current_time = shoot_time;
    physical_grenade.shoot_left();
}

void Grenade::shoot_up(){
    std::time_t current_time = std::time(nullptr);
    current_time = shoot_time;
    physical_grenade.shoot_up();
}

bool Grenade::exploded(std::vector<Bullet> &bullets, std::vector<MapPoint> &other_objects){

    std::time_t current_time = std::time(nullptr);
    if (current_time - shoot_time >= detonation_time){
        int j = 1;
        for (int i = 0; i <= 6 ; i++){
            (i<3)? j ++ : j --;
            Tuple position = physical_grenade.get_position();
            bullets.push_back(Bullet(position.x, position.y, 4, TypeDynamicObject::GRENADE_PROJECTILE, id_player));
            bullets.back().add_speed(-3 + i, j);
        }
        return true;
    }
    return false;
}

