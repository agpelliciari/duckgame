#include "physical_player.h"

#include <iostream>

PhysicalPlayer::PhysicalPlayer(int init_coord_x, int init_coord_y):
        PhysicalObject(init_coord_x, init_coord_y, 16, 22),
        initial_position{init_coord_x, init_coord_y},
        flap_attemps(10),
        on_air(true) {}

void PhysicalPlayer::update_action(TypeMoveAction& move_action) {
    move_action = TypeMoveAction::NONE;
    if (speed.x > 0) {
        move_action = TypeMoveAction::MOVE_RIGHT;
    }
    if (speed.x < 0) {
        move_action = TypeMoveAction::MOVE_LEFT;
    }
    if (speed.y > 0) {
        move_action = TypeMoveAction::AIR_NEUTRAL;
    }
    if (speed.y > 0 && speed.x > 0) {
        move_action = TypeMoveAction::AIR_RIGHT;
    }
    if (speed.y > 0 && speed.x < 0) {
        move_action = TypeMoveAction::AIR_LEFT;
    }
    if (flap_attemps < 10 && flap_attemps > 0){
        move_action = TypeMoveAction::FLAP_NEUTRAL;
    }
    if (flap_attemps < 10 && flap_attemps > 0 && speed.x > 0) {
        move_action = TypeMoveAction::FLAP_RIGHT;
    }
    if (flap_attemps < 10 && flap_attemps > 0 && speed.x < 0) {
        move_action = TypeMoveAction::FLAP_LEFT;
    }
}




void PhysicalPlayer::react_to_sides_collision(bool is_player, int id_player){
    if (!is_player) {
        speed.x = 0;
    }

}

void PhysicalPlayer::react_to_down_collision(bool is_player, int id_player){
    if (!is_player) {
        speed.y = 0;
    }
}

void PhysicalPlayer::react_to_up_collision(bool is_player, int id_player){
    if (!is_player) {
        speed.y = 0;
        acceleration.y = -10;
        flap_attemps = 10;
    }
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
