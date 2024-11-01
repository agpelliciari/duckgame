#include <iostream>
#include "physical_object.h"

PhysicalObject::PhysicalObject(int init_coord_x, int init_coord_y, int dimension_x,
                       int dimension_y, int speed_x, int speed_y, int gravity_):
                        initial_position{init_coord_x, init_coord_y},
                        actual_position{init_coord_x, init_coord_y},
                        dimension{dimension_x, dimension_y},
                        speed{speed_x, speed_y},
                        gravity(-gravity_), time_step(0.4), flap_attemps(0){}

void PhysicalObject::add_speed(int speed_x, int speed_y){
    if (this->speed.x >= -10 && this->speed.x <= 10){
        this->speed.x += speed_x;
    }

    if (this->speed.y <= 0 ) {
        this->speed.y += speed_y;
    } else {
        if (flap_attemps < 3 && actual_position.y >= 0) {
            std::cout << "speed_y antes = " << this->speed.y << std::endl;
            this->speed.y += speed_y * 0.2;
            std::cout << "speed_y despues = " << this->speed.y << std::endl;
            flap_attemps++;
            std::cout << "aleteos: " << flap_attemps << std::endl;
        }
    }
}

void PhysicalObject::move(){
    //falta chequear colisiones con objetos
    actual_position.x += speed.x * time_step;
    if (actual_position.y >= 0) {
        actual_position.y += speed.y * time_step;
        speed.y += gravity * time_step;
        if (actual_position.y < 0) {
            actual_position.y = 0;
            speed.y = 0;
            flap_attemps = 0;
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
    //transformo las coordenadas de y para que sean compatibles
    //con las coordenadas de la interfaz
    coord_y = 300 - actual_position.y;
}

//PhysicalObject::~PhysicalObject(){}


