#ifndef COLLISION_H
#define COLLISION_H

#include "type_collision.h"

struct Collision {
    int id;
    CollisionTypeMap type;

    Collision(int id, CollisionTypeMap type) : id(id), type(type) {}
};

#endif // COLLISION_H
