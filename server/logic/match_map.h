#ifndef MATCH_MAP_H
#define MATCH_MAP_H

#include <vector>
#include "map_object.h"
#include "tuple.h"
#include "collision.h"
#include "type_collision.h"

class MatchMap {

private:
    int width;                                // cppcheck-suppress unusedStructMember
    int height;                               // cppcheck-suppress unusedStructMember
    std::vector<std::vector<bool>> game_map;  // cppcheck-suppress unusedStructMember
    std::vector<MapObjectServer> objects;     // cppcheck-suppress unusedStructMember

public:
    MatchMap(int size_x, int size_y);

    void add_temp_collision(const int x, const int y);

    void add_collision(Tuple position, Tuple dimension, CollisionTypeMap type, int id);
    void clear_objects();

    bool out_of_map(int position_x, int position_y, int dimension_x, int dimension_y) const;
    int getWidth() const;
    int getHeight() const;

    bool out_of_map_y(const int y) const;
    bool out_of_map_x(const int x) const;

    bool check_collision(const int x, const int y, CollisionTypeMap &type, int &id) const;
    bool check_horizontal_collision(const int x, const int y) const;
    bool check_vertical_collision(const int x, const int y) const;
};


#endif  // MATCH_LOGIC_H
