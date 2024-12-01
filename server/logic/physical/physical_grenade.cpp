

#include "physical_grenade.h"

PhysicalGrenade::PhysicalGrenade(int init_coord_x, int init_coord_y):
        PhysicalObject(init_coord_x, init_coord_y, 5, 5),
        impacted(false), impacted_collision{0, CollisionTypeMap::NONE}, out_of_map(false){
        acceleration.y = -3;
        }

void PhysicalGrenade::react_to_sides_collision(Collision collision) {
        if (speed.x == 0){
                return;
        } else {
            //hago que rebote si choca una pared
                speed.x = -speed.x / 2;
        }
}

void PhysicalGrenade::react_to_out_of_map() {
        out_of_map = true;
}

void PhysicalGrenade::react_to_down_collision(Collision collision) {
        this->impact_with_up_or_down_collision();
}

void PhysicalGrenade::react_to_up_collision(Collision collision) {
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

