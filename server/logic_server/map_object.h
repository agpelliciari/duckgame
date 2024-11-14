
#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "tuple.h"


struct MapObjectServer {
    struct Tuple map_point; // cppcheck-suppress unusedStructMember
    struct Tuple dimension; // cppcheck-suppress unusedStructMember
    bool is_player;
    int id_player;
    MapObjectServer(const struct Tuple& position_, const struct Tuple& dimension_,
                    const bool is_player_, const int id_player_):
            map_point(position_.x, position_.y), dimension(dimension_.x, dimension_.y),
            is_player(is_player_), id_player(id_player_) {}

};


#endif //MAP_OBJECT_H
