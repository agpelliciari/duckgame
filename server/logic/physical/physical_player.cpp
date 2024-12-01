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
        last_dir_ind(RIGHT_IND),
        moving_dir(NOT_SETTED),
        on_air(false), out_of_map(false),hold_flap(false),
        is_stay_down(false),
        collided_sides(false) {
        
        acceleration.y = -configs.gravity;
        
        }
        
bool PhysicalPlayer::isOnAir() const{
     return on_air || speed.y != 0;
}

void PhysicalPlayer::update_action(TypeMoveAction& move_action) {

    if(is_stay_down){
        move_action = TypeMoveAction::STAY_DOWN; // No se diferencian entre left/right?
        return;
    }
    
    int dir_ind = NEUTRAL_IND;
    if(moving_dir != NOT_SETTED){
        dir_ind = (int)moving_dir + 1;
        if(dir_ind == NEUTRAL_IND && speed.x != 0){
            dir_ind = last_dir_ind;
        } else{
            last_dir_ind= dir_ind;        
        }
    }

    if(isOnAir()){
        if(hold_flap || flap_attemps < configs.player_flaps){
           move_action = MOVE_ON_FLAP[dir_ind];
        } else{
           move_action = MOVE_ON_AIR[dir_ind];
        }
    } else {
        move_action = MOVE_ON_GROUND[dir_ind];         
    }
    
}

void PhysicalPlayer::react_to_sides_collision(Collision collision){
    stop_moving_x();
    collided_sides = true;
}

void PhysicalPlayer::react_to_down_collision(Collision collision){
        speed.y = 0;
        acceleration.y = -configs.gravity;
        flap_attemps = configs.player_flaps;
        hold_flap = false;
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
    impulses.clear();
    acceleration.x = 0;
}


bool PhysicalPlayer::stay_down_start(){
    if(isOnAir()){
       return false;
    }
    
    if(is_stay_down){
        return true;
    }

    dimension.y -= 15;
    
    is_stay_down = true;    
    stop_moving_x();
    
    return true;
}

void PhysicalPlayer::stay_down_end(){
    if(is_stay_down){
       dimension.y += 15;
       is_stay_down = false;
       if(hold_flap){
           // setea la gravedad
           acceleration.y = -configs.flap_grav;
       }
       
       if(moving_dir != NOT_SETTED){
           speed.x += (int)moving_dir *  configs.player_speed;    
       }
       //moving_dir = NOT_SETTED; // Reset
    }    
}

bool PhysicalPlayer::try_flap_start(){
    if (speed.y >= 0) {
        return false;
    }
    
    hold_flap = true; // Por mas no flapees marcalo como true! Pero no cambies la gravedad.
    if(is_stay_down){
        return false;
    }
    
    acceleration.y = -configs.flap_grav; // Cambia la gravedad aunque no de el saltito
    if(flap_attemps <= 0){
         return false;
    }
    
    // Pega el saltito.
    speed.y = 0;
    this->add_speed(0, configs.player_flap_force);
    flap_attemps --;
    std::cout << "AFTER FLAP VEL "<< speed.y << "Acc "<< acceleration.y<<std::endl;
    
    return true;
}
bool PhysicalPlayer::jump_start(){
    if (isOnAir() || is_stay_down) {
        return false;
    }
    
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
    
    std::cout << "ADD IMPULSE MAX "<< vel_max << " dur time step : "<< duration<< "then r acc:"<<real_acc << " left:" << left <<std::endl;
    
    std::cout << "acc full " << acc<< "and " <<acceleration.x<<std::endl;

    
    
    struct Impulse& impulse = impulses.emplace_back(left,acc, duration);

}


void PhysicalPlayer::check_moving_dir(const MatchMap& colition_map){

     if(collided_sides){
          if(is_stay_down || (moving_dir != MOVING_LEFT && moving_dir != MOVING_RIGHT)){
               return;
          }
          //std::cout << "SHOULD CHECK START MOVE FOR DIR "<< moving_dir << std::endl;
          Collision collision(0, CollisionTypeMap::NONE);
          if(detect_x_collision(colition_map, (int)moving_dir, collision)){
               return;
          }
          
          collided_sides = false;
          speed.x = ((int)moving_dir) *  configs.player_speed;
          return;
     }
     
     auto itImpulse = impulses.begin();
     
     while(itImpulse != impulses.end()){
          itImpulse->steps--;
          std::cout <<" NOW STEPS "<< itImpulse->steps << "vel x:"<< speed.x << "acc "<< acceleration.x <<std::endl;
          if(itImpulse->steps <= 0){
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
    } else if(moving_dir == NO_MOVE){
        moving_dir= (PlayerMovingDir) ((int)moving_dir - (int)mov_dir);   
    } else{
        std::cout << "IGNORE UNDO OF " << (int) mov_dir<<std::endl;
        return;
    }

    if(collided_sides || is_stay_down){
        return;
    }
    speed.x -= ((int)mov_dir) *  configs.player_speed;    

    
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
    
    if(collided_sides || is_stay_down){
        return;
    }
    
    speed.x += (int)new_dir *  configs.player_speed;    
}
