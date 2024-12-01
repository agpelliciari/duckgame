#include "physical_player.h"

#include <iostream>

PhysicalPlayer::PhysicalPlayer(int init_coord_x, int init_coord_y, const Configuration& _configs):
        PhysicalObject(init_coord_x, init_coord_y, PLAYER_WIDTH, PLAYER_HEIGHT),
        initial_position{init_coord_x, init_coord_y},
        configs(_configs),
        flap_attemps(configs.player_flaps),
        moving_dir(NOT_SETTED),
        on_air(true), out_of_map(false) {
        
        acceleration.y = -configs.gravity;
        
        }
        
bool PhysicalPlayer::isOnAir() const{
     return on_air;
}

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
    if ((flap_attemps < configs.player_flaps && flap_attemps > 0  && acceleration.x == 0)){
        move_action = TypeMoveAction::FLAP_NEUTRAL;
    }
    if ((flap_attemps < configs.player_flaps && flap_attemps > 0 && speed.x > 0  && acceleration.x == 0)) {
        move_action = TypeMoveAction::FLAP_RIGHT;
    }
    if ((flap_attemps < configs.player_flaps && flap_attemps > 0 && speed.x < 0  && acceleration.x == 0)) {
        move_action = TypeMoveAction::FLAP_LEFT;
    }
}

void PhysicalPlayer::react_to_sides_collision(Collision collision){
        speed.x = 0;
}

void PhysicalPlayer::react_to_down_collision(Collision collision){
        speed.y = 0;
        acceleration.y = -configs.gravity;
        flap_attemps = configs.player_flaps;
        on_air = false;
}

void PhysicalPlayer::react_to_up_collision(Collision collision){
        speed.y = 0;
        acceleration.y = -configs.gravity;
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
            this->add_speed(0, configs.player_flap_force);
            acceleration.y = -3;
            flap_attemps --;
        }
    } else {
        //std::cout << "JMP FORCE ES " << configs.player_jmp_force<< std::endl;
        add_speed(0, configs.player_jmp_force);
        on_air = true;
    }
}

void PhysicalPlayer::jump_end(){
    acceleration.y = -configs.gravity;
}

void PhysicalPlayer::check_moving_dir(const MatchMap& colition_map){
     if((moving_dir == MOVING_LEFT || moving_dir == MOVING_RIGHT) && speed.x ==0){
          //std::cout << "SHOULD CHECK START MOVE FOR DIR "<< moving_dir << std::endl;
          Collision collision(0, CollisionTypeMap::NONE);
          
          if(detect_x_collision(colition_map, (int)moving_dir, collision)){
               return;
          }
          speed.x = ((int)moving_dir) *  configs.player_speed;
          
     }
}

void PhysicalPlayer::undo_moving(PlayerMovingDir mov_dir){
    if(moving_dir == mov_dir){
        moving_dir = NO_MOVE;
        return;
    }
    
    if(moving_dir == NO_MOVE){
        moving_dir= (PlayerMovingDir) ((int)moving_dir - (int)mov_dir);    
        speed.x = ((int)moving_dir) *  configs.player_speed;    
    }
    
}

void PhysicalPlayer::change_moving(PlayerMovingDir new_dir){
    if(moving_dir == new_dir){
        std::cerr << "-----> WANTED SET TO SAME DIR AGAIN OR OPPOSITE WITH OUT UNDO!? NO DEBERIA PASAR!\n";
        return;
    }
    if((int)moving_dir == -(int)new_dir){
        moving_dir= NO_MOVE;    
    } else{
        moving_dir= new_dir;    
    }
    
    speed.x = moving_dir *  configs.player_speed;    
}
