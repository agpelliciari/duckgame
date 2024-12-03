

#include "banana.h"
#include <iostream>
Banana::Banana(int init_coord_x, int init_coord_y, int id_player_):
          id_player(id_player_),  physical_banana(init_coord_x, init_coord_y, false)//,
          //collision(0, CollisionTypeMap::NONE)
          {
}


void Banana::get_pos(int &pos_x, int &pos_y){
    physical_banana.get_map_info(pos_x, pos_y);
}

void Banana::get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type_){
    physical_banana.get_map_info(pos_x, pos_y);
    type_ = TypeDynamicObject::THROWN_BANANA;
}

void Banana::shoot_right(){
    physical_banana.shoot_right();
}

void Banana::shoot_left(){
    physical_banana.shoot_left();
}

void Banana::shoot_up(){
    physical_banana.shoot_up();
}


bool Banana::get_action(const MatchMap& colition_map, ThrowableAction& action){
    physical_banana.move(colition_map);
    if(physical_banana.out_of_map){
        action = ThrowableAction::ERASE_SELF;
        //std::cout << "OUT OF MAP?! BANANA?!\n";
        return true;
    }
    
    if(physical_banana.impacted_player(colition_map, hitted_player)){
        //std::cout << "FOUND PLAYER !?! "<< hitted_player<<" \n";
        action = ThrowableAction::SLIP_PLAYER;
        return true;
    }
    
    //std::cout << "NOTHING BANANA!!?! "<< (int) physical_banana.get_impacted()<<" \n";
    
    return false;
}

// En absoluto ideal. Pero para no refactorizar de mas....
// Retorna el id a un objeto target i.e player para la banana a la que se aplica.
int Banana::activate(std::vector<Bullet> &bullets, std::vector<GameEvent>& events){
    
    
    int pos_x =0;
    int pos_y = 0;
    physical_banana.get_map_info(pos_x, pos_y);
    
    events.emplace_back(pos_x, pos_y, GameEventType::BANANA_EXPLOSION);    
    
    return hitted_player;
}
