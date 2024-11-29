
#include "bullet.h"

Bullet::Bullet(int init_coord_x, int init_coord_y, int range_, TypeDynamicObject type_, int id_player_):
        physical_bullet(init_coord_x, init_coord_y), range(range_ * 16), type(type_), id_player(id_player_), speed{0, 0}{}

void Bullet::move(const MatchMap& colition_map){
    physical_bullet.move(colition_map);
    range -= (speed.x * 0.4 + speed.y * 0.4);
}

void Bullet::get_data(bool &impacted, CollisionTypeMap &type, int &id){

    physical_bullet.get_data(impacted, type, id);
    if (impacted){
        if (type == CollisionTypeMap::PLAYER && id == id_player){
            physical_bullet.reset_data();
            physical_bullet.get_data(impacted, type, id);
            return;
        }
    } else {
        if (range <= 0){
            impacted = true;
            type = CollisionTypeMap::BLOCK;
            id = 0;
        }
    }
}

void Bullet::shoot_up(){
    physical_bullet.shoot_up();
}

void Bullet::shoot_left(){
    physical_bullet.shoot_left();
}

void Bullet::shoot_right(){
    physical_bullet.shoot_right();
}

void Bullet::get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type_){
    physical_bullet.get_map_info(pos_x, pos_y);
    type_ = this->type;
}

void Bullet::add_speed(int speex_x, int speex_y){
    speed.x += speex_x;
    speed.y += speex_y;
    physical_bullet.add_speed(speex_x, speex_y);
}
