
#include "throwable.h"

Throwable::Throwable(int init_coord_x, int init_coord_y, TypeDynamicObject type_, int id_player_, bool is_banana):
    id_player(id_player_), alive(true), physical_grenade(init_coord_x, init_coord_y, is_banana), type(type_){}

void Throwable::move(const MatchMap& colition_map){
    physical_grenade.move(colition_map);
}

void Throwable::get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type_){
    physical_grenade.get_map_info(pos_x, pos_y);
    type_ = this->type;
}

void Throwable::get_pos(int &pos_x, int &pos_y){
    physical_grenade.get_map_info(pos_x, pos_y);
}


bool Throwable::out_of_map(){
    return physical_grenade.out_of_map;
}
