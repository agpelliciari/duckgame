
#include "bullet.h"

Bullet::Bullet(int init_coord_x, int init_coord_y, int range_, TypeDynamicObject type_, int id_player_):
        physical_bullet(init_coord_x, init_coord_y), range(range_ * 16), type(type_),
        id_player(id_player_), speed{0, 0}, bounce(false){}

Bullet::Bullet(int init_coord_x, int init_coord_y, int range_, TypeDynamicObject type_, int id_player_, bool bounce_):
        physical_bullet(init_coord_x, init_coord_y), range(range_ * 16), type(type_),
        id_player(id_player_), speed{0, 0}, bounce(bounce_){}


void Bullet::move(const MatchMap& colition_map){
    physical_bullet.move(colition_map);

    int speed_x;
    int speed_y;
    (speed.x < 0) ? speed_x = -speed.x : speed_x = speed.x;
    (speed.y < 0) ? speed_y = -speed.y : speed_y = speed.y;

    range -= (speed_x * 0.4 + speed_y * 0.4);
}

void Bullet::get_data(bool &impacted, CollisionTypeMap &type, int &id){

    physical_bullet.get_data(impacted, type, id);
    if (impacted){
        if (type == CollisionTypeMap::PLAYER && id == id_player){
            physical_bullet.reset_data();
            physical_bullet.get_data(impacted, type, id);
            return;
        }
        if (type == CollisionTypeMap::BLOCK && bounce && range > 0){
            physical_bullet.reset_data();
            physical_bullet.get_data(impacted, type, id);
            physical_bullet.bounce();
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
