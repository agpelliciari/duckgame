
#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "tuple.h"


struct MapObjectServer {
    struct Tuple map_point; // cppcheck-suppress unusedStructMember
    struct Tuple dimension; // cppcheck-suppress unusedStructMember

    MapObjectServer(const struct Tuple& position_, const struct Tuple& dimension_):
            map_point(position_.x, position_.y), dimension(dimension_.x, dimension_.y) {}

};


#endif //MAP_OBJECT_H
