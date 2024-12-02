

#include "grenade.h"
#include <ctime>



Grenade::Grenade(int init_coord_x, int init_coord_y, int id_player_, int time):
          detonation_time(4), shoot_time(time),
          id_player(id_player_), alive(true), physical_grenade(init_coord_x, init_coord_y, true)
          {
}


void Grenade::get_pos(int &pos_x, int &pos_y){
    physical_grenade.get_map_info(pos_x, pos_y);
}

void Grenade::get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type_){
    physical_grenade.get_map_info(pos_x, pos_y);
    type_ = TypeDynamicObject::GRANADA;
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


bool Grenade::get_action(const MatchMap& colition_map, ThrowableAction& action){
    physical_grenade.move(colition_map);
    if(physical_grenade.out_of_map){
        action = ERASE_SELF;
        return true;
    }
    
    if((std::time(nullptr) - shoot_time) >= detonation_time){
        action = EXPLODE_SELF;
        return true;
    }
    
    return false;
}

// En absoluto ideal. Pero para no refactorizar de mas....
// Retorna el id a un objeto target i.e player para la banana a la que se aplica.
int Grenade::activate(std::vector<Bullet> &bullets, std::vector<GameEvent>& events){
    int j = 1;
    Tuple position = physical_grenade.get_position();
    
    for (int i = 0; i <= 6 ; i++){
        (i<3)? j ++ : j --;
        bullets.push_back(Bullet(position.x, position.y, 4, TypeDynamicObject::GRENADE_PROJECTILE, id_player));
        bullets.back().add_speed(-3 + i, j);
    }
    
    events.emplace_back(position.x, position.y,GameEventType::GRENADE_EXPLOSION);
    
    return -1;
}
