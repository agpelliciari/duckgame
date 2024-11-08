
#include "physical_object.h"

PhysicalObject::PhysicalObject(int position_x, int position_y, int dimension_x, int dimension_y):
        position{position_x, position_y}, dimension{dimension_x, dimension_y}, speed{0, 0}, acceleration{0, -10},
        time_step(0.4) {}

void PhysicalObject::add_speed(int speed_x, int speed_y) {
    this->speed.x += speed_x;
    this->speed.y += speed_y;
}

void PhysicalObject::add_acceleration(int acceleration_x, int acceleration_y) {
    this->acceleration.x += acceleration_x;
    this->acceleration.y += acceleration_y;
}

bool PhysicalObject::detect_x_collision(const MatchMap& colition_map){

    if (colition_map.out_of_map_x(position.x - 1) ||
        colition_map.out_of_map_x(position.x + dimension.x + 1) ||
        colition_map.out_of_map_y(position.y) ||
        colition_map.out_of_map_y(position.y + dimension.y)) {
        return true;
    }

    for (int y = 0; y <= dimension.y; y++) {
        if (colition_map.check_collision(position.x + dimension.x + 1, position.y + y) && speed.x > 0) {
            return true;
        }

        if (colition_map.check_collision(position.x - 1, position.y + y) && speed.x < 0) {
            return true;
        }
    }

    return false;
}

bool PhysicalObject::detect_y_collision(const MatchMap& colition_map){

    if (colition_map.out_of_map_y(position.y - 1) || colition_map.out_of_map_y(position.y + dimension.y + 1)) {
        return true;
    }

    for (int x = 0; x <= dimension.x && (position.x + x) < colition_map.getWidth(); x++) {
        if (colition_map.check_collision(position.x + x, position.y - 1) && speed.y <= 0) {
            return true;
        }
        if (colition_map.check_collision(position.x + x, position.y + dimension.y + 1) && speed.y > 0) {
            return true;
        }
    }

    return false;
}

void PhysicalObject::move(const MatchMap& colition_map){

    if (speed.x != 0){
        int sign;
        speed.x > 0 ? sign = 1 : sign = -1;
        for (int x = 0; x <= speed.x * time_step * sign; x++) {
            if (detect_x_collision(colition_map)) {
                this->react_to_sides_collision();
            } else {
                position.x += 1 * sign;
            }
        }
    }

    speed.y += acceleration.y * time_step;
    if (speed.y <= 0){
        for (int y = 0; y >= speed.y * time_step; y--) {
            if (detect_y_collision(colition_map) ) {
               this->react_to_down_collision();
            } else {
                position.y--;
            }
        }
    } else {
        for (int y = 0; y <= speed.y * time_step; y++) {
            if (detect_y_collision(colition_map)) {
                this->react_to_up_collision();
            } else {
                position.y++;
            }
        }
    }

}


Tuple PhysicalObject::get_position(){
    return position;
}

void PhysicalObject::get_real_position(int &x, int &y){
    x = position.x;
    y = -position.y;
}

Tuple PhysicalObject::get_dimension(){
    return dimension;
}
