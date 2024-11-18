
#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "tuple.h"
#include "collision.h"
#include "type_collision.h"

struct MapObjectServer {
    struct Tuple map_point; // cppcheck-suppress unusedStructMember
    struct Tuple dimension; // cppcheck-suppress unusedStructMember
    struct Collision collision; // cppcheck-suppress unusedStructMember

    // Constructor
    MapObjectServer(const struct Tuple& position_, const struct Tuple& dimension_,
                    CollisionTypeMap type, int id)
        : map_point(position_.x, position_.y),
          dimension(dimension_.x, dimension_.y),
          collision(id, type) {}
};

#endif // MAP_OBJECT_H

