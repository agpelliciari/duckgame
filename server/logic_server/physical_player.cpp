#include "physical_player.h"

#include <iostream>

PhysicalPlayer::PhysicalPlayer(int init_coord_x, int init_coord_y):
        PhysicalObject(init_coord_x, init_coord_y, PLAYER_WIDTH, PLAYER_HEIGHT),
        initial_position{init_coord_x, init_coord_y},
        flap_attemps(FLAP_ATTEMPS),
        on_air(true), out_of_map(false) {}

void PhysicalPlayer::update_action(TypeMoveAction& move_action) {
    move_action = TypeMoveAction::NONE;
    if ((speed.x > 0 && acceleration.x == 0) || (speed.x < 0 && acceleration.x > 0)) {
        move_action = TypeMoveAction::MOVE_RIGHT;
    }
    if ((speed.x < 0  && acceleration.x == 0) || (speed.x > 0 && acceleration.x < 0)) {
        move_action = TypeMoveAction::MOVE_LEFT;
    }
    if ((speed.y > 0  && acceleration.x == 0) ) {
        move_action = TypeMoveAction::AIR_NEUTRAL;
    }
    if ((speed.y > 0 && speed.x > 0  && acceleration.x == 0) || (speed.y >0 && speed.x < 0 && acceleration.x > 0)) {
        move_action = TypeMoveAction::AIR_RIGHT;
    }
    if ((speed.y > 0 && speed.x < 0  && acceleration.x == 0) || (speed.y > 0 && speed.x > 0 && acceleration.x < 0)) {
        move_action = TypeMoveAction::AIR_LEFT;
    }
    if ((flap_attemps < 10 && flap_attemps > 0  && acceleration.x == 0)){
        move_action = TypeMoveAction::FLAP_NEUTRAL;
    }
    if ((flap_attemps < 10 && flap_attemps > 0 && speed.x > 0  && acceleration.x == 0)) {
        move_action = TypeMoveAction::FLAP_RIGHT;
    }
    if ((flap_attemps < 10 && flap_attemps > 0 && speed.x < 0  && acceleration.x == 0)) {
        move_action = TypeMoveAction::FLAP_LEFT;
    }
}

void PhysicalPlayer::react_to_sides_collision(Collision collision){
        speed.x = 0;
}

void PhysicalPlayer::react_to_down_collision(Collision collision){
        speed.y = 0;
        acceleration.y = -10;
        flap_attemps = 10;
        on_air = false;
}

void PhysicalPlayer::react_to_up_collision(Collision collision){
        speed.y = 0;
        acceleration.y = -10;
}

void PhysicalPlayer::react_to_out_of_map() {
    out_of_map = true;
}

bool PhysicalPlayer::is_out_of_map() {
    return out_of_map;
}

void PhysicalPlayer::stop_moving_x(){
    speed.x = 0;
}


void PhysicalPlayer::stay_down_start(){
    dimension.y -= 15;
}

void PhysicalPlayer::stay_down_end(){
    dimension.y += 15;
}

void PhysicalPlayer::jump_start(){
    if (on_air) {
        if (speed.y < 0 && flap_attemps > 0) {
            this->add_speed(0, 10);
            acceleration.y = -3;
            flap_attemps --;
        }
    } else {
        add_speed(0, 50);
        on_air = true;
    }
}

void PhysicalPlayer::jump_end(){
    acceleration.y = -10;
}
