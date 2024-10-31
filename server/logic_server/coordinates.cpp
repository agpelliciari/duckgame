#include <iostream>
#include "coordinates.h"

Coordinates::Coordinates(int init_x, int init_y):
        initial_x(init_x), initial_y(init_y), actual_x(init_x), actual_y(init_y), step(1),
        jump_step(20), actual_jump_step(0), actual_fall_step(2){}

void Coordinates::get_coordinates(int& x, int& y) {
    x = this->actual_x;
    y = this->actual_y + 300;
}

void Coordinates::move_right() { this -> actual_x += step; }

void Coordinates::move_left() { this -> actual_x -= step; }

void Coordinates::jump() {
    if (actual_y == 0){
    	actual_y = jump_step;
    	actual_jump_step = jump_step;
    	actual_y = -actual_jump_step;
    }

}

void Coordinates::update_position_y(){
	if (actual_jump_step > 0){
        actual_jump_step = actual_jump_step * 0.8;
        actual_y -= actual_jump_step;
        if (actual_jump_step <= 2){
            actual_jump_step = 0;
        }
	} else if (actual_y < 0){
        actual_y += actual_fall_step;
        actual_fall_step = actual_fall_step * 1.5;
        if (actual_y >= -5){
            actual_y = 0;
            actual_fall_step = 2;
        }
	}

}
