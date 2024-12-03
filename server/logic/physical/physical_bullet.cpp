
#include "physical_bullet.h"
#include <iostream>
PhysicalBullet::PhysicalBullet(int init_coord_x, int init_coord_y):
        PhysicalObject(init_coord_x, init_coord_y, 5, 5),
        impacted(false), impacted_collision{0, CollisionTypeMap::NONE},
        impacted_up_or_down(false), impacted_sides(false)
         /*,
        type(TypeDynamicObject::PROJECTILE)*/{
        acceleration.y = 0;
        }

/*PhysicalBullet::PhysicalBullet(int init_coord_x, int init_coord_y, TypeDynamicObject type_):
        PhysicalObject(init_coord_x, init_coord_y, 5, 5),
        impacted(false), impacted_collision{0, CollisionTypeMap::NONE},
        type(type_){
        acceleration.y = 0;
        }*/

void PhysicalBullet::shoot_up(){
        this->add_speed(0, 5);
}

void PhysicalBullet::shoot_left(){
        this->add_speed(-5, 0);
}

void PhysicalBullet::shoot_right(){
        this->add_speed(5, 0);
}

void PhysicalBullet::react_to_sides_collision(Collision collision) {
        std::cout << "BULLET COLLISION side WITH OBJ! type: "<< (int)collision.type<< " id:"<< collision.id<<"\n";

        impacted = true;
        impacted_collision = collision;
        impacted_sides = true;
}
void PhysicalBullet::react_to_down_collision(Collision collision) {
        std::cout << "BULLET COLLISION down WITH OBJ! type: "<< (int)collision.type<< " id:"<< collision.id<<"\n";
        impacted = true;
        impacted_collision = collision;
        impacted_up_or_down = true;
}

void PhysicalBullet::react_to_up_collision(Collision collision) {
        std::cout << "BULLET COLLISION up WITH OBJ! type: "<< (int)collision.type<< " id:"<< collision.id<<"\n";
        impacted = true;
        impacted_collision = collision;
        impacted_up_or_down = true;
}

void PhysicalBullet::react_to_out_of_map(){
        std::cout << "BULLET REACT OUT OF MAP!\n";
        impacted = true;
        impacted_collision = Collision(0, CollisionTypeMap::BLOCK);
}

void PhysicalBullet::get_data(bool &impacted_, CollisionTypeMap &type_, int &id_){
    impacted_ = impacted;
    type_ = impacted_collision.type;
    id_ = impacted_collision.id;
}

void PhysicalBullet::get_map_info(int &pos_x, int &pos_y){
    pos_x = this->get_position().x;
    pos_y = this->get_position().y;
}

void PhysicalBullet::reset_data(){
    impacted = false;
    impacted_collision = {0, CollisionTypeMap::NONE};
}

void PhysicalBullet::bounce(){
    if (impacted_sides) {
        speed.x = -speed.x;
    }
    if (impacted_up_or_down) {
        speed.y = -speed.y;
    }
}
