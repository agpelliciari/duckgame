
#include "physical_object.h"

PhysicalObject::PhysicalObject(int init_coord_x, int init_coord_y, int dimension_x,
                       int dimension_y, int speed_x, int speed_y, int gravity_):
                        initial_position{init_coord_x, init_coord_y},
                        actual_position{init_coord_x, init_coord_y},
                        dimension{dimension_x, dimension_y},
                        speed{speed_x, speed_y},
                        gravity(-gravity_), time_step(0.4){}

void PhysicalObject::add_speed(int speed_x, int speed_y){
    this->speed.x += speed_x;
    if (this->speed.y == 0) {
        this->speed.y += speed_y;
    } else {
        this->speed.y += speed_y * 0.4;
    }
}

void PhysicalObject::move(){
    //falta chequear colisiones con objetos
    actual_position.x += speed.x * time_step;
    if (actual_position.y > 0) {
        actual_position.y += speed.y * time_step;
        speed.y += gravity * time_step;
        if (actual_position.y <= 0) {
            actual_position.y = 0;
            speed.y = 0;
        }
    }
}

void PhysicalObject::stop_moving_x(){
    speed.x = 0;
}

void PhysicalObject::stop_moving_y(){
    speed.y = 0;
}

void PhysicalObject::get_position(int &coord_x, int &coord_y){
    coord_x = actual_position.x;
    coord_y = actual_position.y;
}

//PhysicalObject::~PhysicalObject(){}


