

#include "grenade.h"
#include <ctime>

Grenade::Grenade(int init_coord_x, int init_coord_y, TypeDynamicObject type_, int id_player_, int time):
        id_player(id_player_), detonation_time(4), alive(true),
        physical_grenade(init_coord_x, init_coord_y), type(type_), shoot_time(time){}

void Grenade::move(const MatchMap& colition_map){
    physical_grenade.move(colition_map);
}

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

bool Grenade::exploded(std::vector<Bullet> &bullets){

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

void Grenade::get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type_){
    physical_grenade.get_map_info(pos_x, pos_y);
    type_ = this->type;
}

void Grenade::get_pos(int &pos_x, int &pos_y){
    physical_grenade.get_map_info(pos_x, pos_y);
}


bool Grenade::out_of_map(){
    return physical_grenade.out_of_map;
}
