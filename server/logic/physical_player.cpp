#include "physical_player.h"

#include <iostream>

static TypeMoveAction MOVE_ON_AIR[3] = {TypeMoveAction::AIR_LEFT,TypeMoveAction::AIR_NEUTRAL, TypeMoveAction::AIR_RIGHT};
static TypeMoveAction MOVE_ON_FLAP[3] = {TypeMoveAction::FLAP_LEFT,TypeMoveAction::FLAP_NEUTRAL, TypeMoveAction::FLAP_RIGHT};
static TypeMoveAction MOVE_ON_GROUND[3] = {TypeMoveAction::MOVE_LEFT,TypeMoveAction::NONE, TypeMoveAction::MOVE_RIGHT};

#define NEUTRAL_IND 1
#define LEFT_IND 0
#define RIGHT_IND 2

PhysicalPlayer::PhysicalPlayer(int init_coord_x, int init_coord_y, const Configuration& _configs):
        PhysicalObject(init_coord_x, init_coord_y, PLAYER_WIDTH, PLAYER_HEIGHT),
        initial_position{init_coord_x, init_coord_y},
        configs(_configs),
        flap_attemps(configs.player_flaps),
        steps_deaccelerate(-1),
        moving_dir(NOT_SETTED),
        on_air(true), out_of_map(false),hold_flap(false),stopped_x(false) {
        
        acceleration.y = -configs.gravity;
        
        }
        
bool PhysicalPlayer::isOnAir() const{
     return on_air;
}

void PhysicalPlayer::update_action(TypeMoveAction& move_action) {
    move_action = TypeMoveAction::NONE;
    int dir_ind = moving_dir == NOT_SETTED? 1 : (int)moving_dir + 1;
    
    if(dir_ind == NEUTRAL_IND){
        if(speed.x > 0){
             dir_ind = RIGHT_IND;
        } else if (speed.x< 0){
             dir_ind = LEFT_IND;        
        }
    }

    if(on_air){
        if(hold_flap || speed.y <= 0){
           move_action = MOVE_ON_FLAP[dir_ind];
        } else{
           move_action = MOVE_ON_AIR[dir_ind];
        }
    } else {
        move_action = MOVE_ON_GROUND[dir_ind];         
    }
    
}

void PhysicalPlayer::react_to_sides_collision(Collision collision){
        speed.x = 0;
        stopped_x = true;
        impulses.clear();
        acceleration.x = 0;
}

void PhysicalPlayer::react_to_down_collision(Collision collision){
        speed.y = 0;
        acceleration.y = -configs.gravity;
        flap_attemps = configs.player_flaps;
        on_air = false;
        hold_flap = false;
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
    stopped_x = true;
    impulses.clear();
    acceleration.x = 0;
}


void PhysicalPlayer::stay_down_start(){
    dimension.y -= 15;
    
    stopped_x = true;
    impulses.clear();
    acceleration.x = 0;
    speed.x = 0;
}

void PhysicalPlayer::stay_down_end(){
    dimension.y += 15;
}

bool PhysicalPlayer::try_flap_start(){
    if (speed.y < 0 && flap_attemps > 0) {
        this->add_speed(0, configs.player_flap_force);
        
        hold_flap = true;
        acceleration.y = -3;
        flap_attemps --;
        return true;
    }
    
    return false;
}
bool PhysicalPlayer::jump_start(){
    if (on_air) {
        return false;
    }
    hold_flap = false;
    
    //std::cout << "JMP FORCE ES " << configs.player_jmp_force<< std::endl;
    add_speed(0, configs.player_jmp_force);
    on_air = true;
    return true;
}

void PhysicalPlayer::jump_end(){ 
    if(hold_flap){
        std::cout<< "WAS FLAP END!!!\n";
        hold_flap = false;
        acceleration.y = -configs.gravity;
    }
    std::cout<< "JUMP END?!!!\n";
}

void PhysicalPlayer::add_impulse_x(int vel_max, int duration){
    this->speed.x += vel_max;

    int acc = -((vel_max/duration));
    
    this->acceleration.x += acc;
    
    int real_acc = (float)(acc)*time_step;
    duration = -vel_max/real_acc; // puede haber redondeo!
    
    int left = vel_max + real_acc*duration;
    
    //std::cout << "ADD IMPULSE MAX "<< vel_max << " dur time step : "<< duration<< "then r acc:"<<real_acc << " left:" << left <<std::endl;
    
    //std::cout << "acc full " << acc<< "and " <<acceleration.x<<std::endl;q

    
    
    struct Impulse& impulse = impulses.emplace_back(left,acc, duration);

}


void PhysicalPlayer::check_moving_dir(const MatchMap& colition_map){
     if(stopped_x && (moving_dir == MOVING_LEFT || moving_dir == MOVING_RIGHT)){
          //std::cout << "SHOULD CHECK START MOVE FOR DIR "<< moving_dir << std::endl;
          Collision collision(0, CollisionTypeMap::NONE);
          
          if(detect_x_collision(colition_map, (int)moving_dir, collision)){
               return;
          }
          stopped_x = false;
          speed.x = ((int)moving_dir) *  configs.player_speed;
          
     }
     
     auto itImpulse = impulses.begin();
     
     while(itImpulse != impulses.end()){
          itImpulse->steps--;
          std::cout <<" NOW STEPS "<< itImpulse->steps << "vel x:"<< speed.x << "acc "<< acceleration.x <<std::endl;
          if(itImpulse->steps < 0){
              speed.x-= itImpulse->left_over_vel;
              acceleration.x-= itImpulse->acc;
              std::cout <<" FINAL? vel "<< speed.x << " acc "<<  itImpulse->acc << "end "<< acceleration.x<<std::endl;
              itImpulse = impulses.erase(itImpulse);
              continue;
          }
     
          ++itImpulse;
     }
}

void PhysicalPlayer::undo_moving(PlayerMovingDir mov_dir){
    if(moving_dir == mov_dir){
        moving_dir = NO_MOVE;
        
        if(stopped_x){
            return;
        }
        stopped_x = false;
        speed.x -= ((int)mov_dir) *  configs.player_speed;    
        //std::cout << " UNDO AT SAME? "<< speed.x<< "\n";
        return;
    }
    
    if(moving_dir == NO_MOVE){
        moving_dir= (PlayerMovingDir) ((int)moving_dir - (int)mov_dir);   
        stopped_x = false;
        speed.x -= ((int)mov_dir) *  configs.player_speed;    
        //std::cout << " UNDO AT NO MOVE?" << speed.x<< "\n";
    }
    
}

void PhysicalPlayer::change_moving(PlayerMovingDir new_dir){
    if(moving_dir == new_dir){
        std::cerr << "-----> WANTED SET TO SAME DIR AGAIN OR OPPOSITE WITH OUT UNDO!? NO DEBERIA PASAR!\n";
        return;
    }
    if((int)moving_dir == -(int)new_dir){
        moving_dir= NO_MOVE;    
        if(stopped_x){
            return;
        }
        speed.x += (int)new_dir *  configs.player_speed;    
    } else{
        moving_dir= new_dir;    
        stopped_x = false;    
        speed.x += (int)new_dir *  configs.player_speed;    
    }
}
