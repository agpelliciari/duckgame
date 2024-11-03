#include <iostream>
#include "physical_object.h"

PhysicalObject::PhysicalObject(int init_coord_x, int init_coord_y, int dimension_x,
                       int dimension_y, int speed_x, int speed_y, int gravity_):
                        initial_position{init_coord_x, init_coord_y},
                        actual_position{init_coord_x, init_coord_y},
                        dimension{dimension_x, dimension_y},
                        speed{speed_x, speed_y},
                        gravity(-gravity_), time_step(0.4), flap_attemps(10){}

void PhysicalObject::add_speed(int speed_x, int speed_y){
    if (this->speed.x >= -10 && this->speed.x <= 10){
        this->speed.x += speed_x;
    }

    if (this->speed.y == 0 ) {
        //salto normal
        if (actual_position.y <=5){
            this->speed.y += speed_y;
        }
    } else if (this->speed.y < 0 ) {
        if (flap_attemps > 0 && actual_position.y > 5) {
            //aleteo en caida libre
            this->speed.y += speed_y * 0.2;
            gravity = -5;
            flap_attemps--;
            std::cout << "Flap attemps: " << flap_attemps << std::endl;
        }
    }
}

void PhysicalObject::move(){
    //falta chequear colisiones con objetos
    actual_position.x += speed.x * time_step;
    if (actual_position.y >= 0) {
        actual_position.y += speed.y * time_step;
        speed.y += gravity * time_step;
        if (actual_position.y < 0 || (actual_position.y <=5 && speed.y < 0)) {
            gravity = -10;
            actual_position.y = 0;
            speed.y = 0;
            flap_attemps = 10;

        }
    }
}

void PhysicalObject::update_action(TypeMoveAction& move_action){
    //std::cout << "speed y: " << speed.y << std::endl;
    move_action = TypeMoveAction::NONE;
    if (speed.x > 0){
        move_action = TypeMoveAction::MOVE_RIGHT;
    }
    if (speed.x < 0){
        move_action = TypeMoveAction::MOVE_LEFT;
    }
    if (speed.y > 0){
        move_action = TypeMoveAction::JUMP;
    }
    if (flap_attemps < 10 && flap_attemps > 0){
        move_action = TypeMoveAction::FLAP;
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


