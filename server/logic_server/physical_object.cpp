#include "physical_object.h"

#include <iostream>

PhysicalObject::PhysicalObject(int init_coord_x, int init_coord_y, int dimension_x, int dimension_y,
                               int speed_x, int speed_y, int gravity_):
        initial_position{init_coord_x, init_coord_y},
        actual_position{init_coord_x, init_coord_y},
        dimension{dimension_x, dimension_y},
        speed{speed_x, speed_y},
        gravity(-gravity_),
        time_step(0.4),
        flap_attemps(10),
        on_air(true) {}

void PhysicalObject::add_speed(int speed_x, int speed_y) {
    if (this->speed.x >= -10 && this->speed.x <= 10) {
        this->speed.x += speed_x;
    }

    if (this->speed.y == 0) {
        // salto normal
        if (!on_air) {
            this->speed.y += speed_y;
            on_air = true;
        }
    } else if (this->speed.y < 0) {
        if (flap_attemps > 0 && actual_position.y > 5) {
            // aleteo en caida libre
            this->speed.y += speed_y * 0.2;
            gravity = -5;
            flap_attemps--;
            // std::cout << "Flap attemps: " << flap_attemps << std::endl;
        }
    }
}

void PhysicalObject::move(const MatchMap& colition_map) {
    // falta chequear colisiones con objetos

    // actual_position.x += speed.x * time_step;

    if (speed.x < 0) {
        for (int x = 0; x >= speed.x * time_step; x--) {
            if (check_left_collision(colition_map)) {
                actual_position.x--;
            } /*else {
                //speed.y = 0;
                actual_position.x +=1;
            }*/
        }
    }
    if (speed.x > 0) {
        for (int x = 0; x <= speed.x * time_step; x++) {
            if (check_right_collision(colition_map)) {
                actual_position.x++;
            } /*else {
                //speed.y = 0;
                actual_position.x -=1;
            }*/
        }
    }

    if (actual_position.y >= 0) {
        speed.y += gravity * time_step;
        // actual_position.y += speed.y * time_step;


        if (speed.y < 0) {
            for (int y = 0; y >= speed.y * time_step; y--) {
                if (check_down_collision(colition_map)) {
                    actual_position.y--;
                } else {
                    // actual_position.y +=1;
                    speed.y = 0;
                    gravity = -10;
                    flap_attemps = 10;
                }
            }
        }

        if (speed.y > 0) {
            for (int y = 0; y <= speed.y * time_step; y++) {
                if (check_up_collision(colition_map)) {
                    actual_position.y++;
                } else {
                    speed.y = 0;
                    // actual_position.y -=1;
                }
            }
        }

        /*if (actual_position.y < 0 || (actual_position.y <=5 && speed.y < 0)) {
            gravity = -10;
            actual_position.y = 0;
            speed.y = 0;
            flap_attemps = 10;
        }*/
    }
}

bool PhysicalObject::check_collision() { return true; }

void PhysicalObject::update_action(TypeMoveAction& move_action) {
    // std::cout << "speed y: " << speed.y << std::endl;
    move_action = TypeMoveAction::NONE;
    if (speed.x > 0) {
        move_action = TypeMoveAction::MOVE_RIGHT;
    }
    if (speed.x < 0) {
        move_action = TypeMoveAction::MOVE_LEFT;
    }
    /*if (speed.y > 0){
        move_action = TypeMoveAction::JUMP;
    }
    if (flap_attemps < 10 && flap_attemps > 0){
        move_action = TypeMoveAction::FLAP;
    }*/
}

void PhysicalObject::stop_moving_x() { speed.x = 0; }

void PhysicalObject::stop_moving_y() { speed.y = 0; }

void PhysicalObject::get_position(int& coord_x, int& coord_y) {

    coord_x = actual_position.x;
    // transformo las coordenadas de y para que sean compatibles
    // con las coordenadas de la interfaz
    coord_y = 300 - actual_position.y;
}

Tuple PhysicalObject::get_real_position() { return actual_position; }


bool PhysicalObject::check_left_collision(const MatchMap& colition_map) {
    if (colition_map.out_of_map_x(actual_position.x - 1) ||
        colition_map.out_of_map_y(actual_position.y) ||
        colition_map.out_of_map_y(actual_position.y + dimension.y)) {
        return false;
    }


    for (int y = 0; y <= dimension.y; y++) {
        if (colition_map.check_collision(actual_position.x - 1, actual_position.y + y)) {
            return false;
        }
    }
    return true;
}

bool PhysicalObject::check_right_collision(const MatchMap& colition_map) {
    if (colition_map.out_of_map_x(actual_position.x + dimension.x + 1) ||
        colition_map.out_of_map_y(actual_position.y) ||
        colition_map.out_of_map_y(actual_position.y + dimension.y)) {
        return false;
    }

    for (int y = 0; y <= dimension.y; y++) {
        if (colition_map.check_collision(actual_position.x + dimension.x + 1,
                                         actual_position.y + y)) {
            return false;
        }
    }

    return true;
}

bool PhysicalObject::check_down_collision(const MatchMap& colition_map) {
    if (colition_map.out_of_map_y(actual_position.y - 1)) {
        std::cout << "Grouuund!\n";
        on_air = false;
        return false;
    }

    for (int x = 0; x <= dimension.x && (actual_position.x + x) < colition_map.getWidth(); x++) {
        if (colition_map.check_collision(actual_position.x + x, actual_position.y - 1)) {
            std::cout << "Over something!\n";
            on_air = false;
            return false;
        }
    }
    on_air = true;
    return true;
}

bool PhysicalObject::check_up_collision(const MatchMap& colition_map) {
    if (colition_map.out_of_map_y(actual_position.y + dimension.y + 1)) {
        return false;
    }

    for (int x = 0; x <= dimension.x && (actual_position.x + x) < colition_map.getWidth(); x++) {
        if (colition_map.check_collision(actual_position.x + x,
                                         actual_position.y + dimension.y + 1)) {
            return false;
        }
    }
    return true;
}

// PhysicalObject::~PhysicalObject(){}
