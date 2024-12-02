

#include "physical_grenade.h"
#include <iostream>
#define WIDTH_GRENADE 5
#define WIDTH_BANANA 10

PhysicalGrenade::PhysicalGrenade(int init_coord_x, int init_coord_y):
        PhysicalObject(init_coord_x, init_coord_y, WIDTH_GRENADE, 5), jitter_on_ground(true), impacted(false), out_of_map(false){
        acceleration.y = -3;
  
    }

PhysicalGrenade::PhysicalGrenade(int init_coord_x, int init_coord_y, bool jitter_on_ground):
        PhysicalObject(init_coord_x, init_coord_y, jitter_on_ground?WIDTH_GRENADE:WIDTH_BANANA
        , 5), jitter_on_ground(jitter_on_ground), impacted(false), out_of_map(false){
        acceleration.y = -3;
}

bool PhysicalGrenade::impacted_player(const MatchMap& colition_map,int& id) const{
     return impacted && colition_map.check_collision_area(CollisionTypeMap::PLAYER, position.x,position.y
    , dimension.x, dimension.y, id);
}

void PhysicalGrenade::react_to_sides_collision(Collision collision) {
        //if(impacted && CollisionTypeMap::PLAYER != collision.type){
        //    std::cout << "IMPACTED BANANA SIDE? PLAYER AT " << position.x << ", " << position.y << std::endl;
        //    return;
        //}


        if (speed.x != 0){
            //hago que rebote si choca una pared
            speed.x = -speed.x / 2;
        }

        
        
}

void PhysicalGrenade::react_to_out_of_map() {
        out_of_map = true;
}

void PhysicalGrenade::react_to_down_collision(Collision collision) {
    if (jitter_on_ground) {
        this->impact_with_up_or_down_collision();
        return;
    } 
    
    if(CollisionTypeMap::PLAYER != collision.type){
        if(impacted){
           return;
        }
        speed.x = 0;
        speed.y = 0;
        impacted = true;
        std::cout << "IMPACTED BANANA? AT " << position.x << ", " << position.y << std::endl;
    //}  else if (impacted){
    //    std::cout << "IMPACTED BANANA? PLAYER AT " << position.x << ", " << position.y << std::endl;
    }

}

void PhysicalGrenade::react_to_up_collision(Collision collision) {
        //if(impacted && CollisionTypeMap::PLAYER != collision.type){
        //    std::cout << "IMPACTED BANANA UP? PLAYER AT " << position.x << ", " << position.y << std::endl;
        //    return;
        //}

        this->impact_with_up_or_down_collision();
}

void PhysicalGrenade::impact_with_up_or_down_collision(){
        speed.y = 0;
        if (speed.x == 0){
                return;
        }
        //le agrego un rozamiento si toca suelo o techo
        if (speed.x > 0){
                acceleration.x = -5;
        }
        if (speed.x < 0){
                acceleration.x = 5;
        }
}


void PhysicalGrenade::get_map_info(int &pos_x, int &pos_y){
    pos_x = position.x;
    pos_y = position.y;
}

void PhysicalGrenade::shoot_right(){
    this->add_speed(5, 5);
}

void PhysicalGrenade::shoot_left(){
    this->add_speed(-5, 5);
}

void PhysicalGrenade::shoot_up(){
    this->add_speed(0, 10);
}

bool PhysicalGrenade::is_out_of_map(){
    return out_of_map;
}

bool PhysicalGrenade::get_impacted(){
    return impacted;
}
