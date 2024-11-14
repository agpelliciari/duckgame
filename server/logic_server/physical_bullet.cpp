
#include "physical_bullet.h"

PhysicalBullet::PhysicalBullet(int init_coord_x, int init_coord_y):
        PhysicalObject(init_coord_x, init_coord_y-23, 5, 5),
        impacted(false), impacted_in_player(false), id_impacted_player(0){
        
        acceleration.y = -1;
        }

void PhysicalBullet::shoot_up(){
        this->add_speed(0, 5);
}

void PhysicalBullet::shoot_left(){
        this->add_speed(-5, 0);
}

void PhysicalBullet::shoot_right(){
        this->add_speed(5, 0);
}

void PhysicalBullet::react_to_sides_collision(bool is_player, int id_player) {
        impacted = true;
        impacted_in_player = is_player;
        id_impacted_player = id_player;
}
void PhysicalBullet::react_to_down_collision(bool is_player, int id_player) {
        impacted = true;
        impacted_in_player = is_player;
        id_impacted_player = id_player;
}

void PhysicalBullet::react_to_up_collision(bool is_player, int id_player) {
        impacted = true;
        impacted_in_player = is_player;
        id_impacted_player = id_player;
}

void PhysicalBullet::get_data(bool &impacted_, bool &impacted_in_player_, int &id_impacted_player_){
    impacted_ = impacted;
    impacted_in_player_ = impacted_in_player;
    id_impacted_player_ = id_impacted_player;
}
