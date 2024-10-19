
#include "coordinates.h"

Coordinates::Coordinates(int init_x, int init_y):initial_x(init_x),initial_y(init_y),
                                                   actual_x(init_x), actual_y(init_y), step(1){}

void Coordinates::get_coordinates(int &x, int &y){
    x = this->actual_x;
    y = this->actual_y;
}

void Coordinates::move_right(){
    actual_x += step;
}

void Coordinates::move_left(){
    actual_x -= step;
}

void Coordinates::jump(){

}

