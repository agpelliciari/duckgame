#include <iostream>
#include "coordinates.h"

Coordinates::Coordinates(int init_x, int init_y):
        initial_x(init_x), initial_y(init_y), actual_x(init_x), actual_y(init_y), step(1) {}

void Coordinates::get_coordinates(int& x, int& y) {
    x = this->actual_x;
    y = this->actual_y;
}

void Coordinates::move_right() {
    this -> actual_x += step;
}

void Coordinates::move_left() {
    this -> actual_x -= step;
}

void Coordinates::jump() {
    this -> speed_y = 10;
}

void Coordinates::update_position_y(){

    if (speed_y > 0){
        actual_y = speed_y * time + 0.5 * gravity * time * time;
        speed_y = speed_y - gravity * time;
    }
    if (speed_y <= 0 && actual_y > 0){
        actual_y = speed_y * time - 0.5 * gravity * time * time;
        speed_y = speed_y + gravity * time;
    }

}
