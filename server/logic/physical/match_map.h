#ifndef MATCH_MAP_H
#define MATCH_MAP_H

#include <vector>
#include "server/logic/physical/map_object.h"
#include "server/logic/physical/tuple.h"
#include "server/logic/physical/collision.h"
#include "type_collision.h"

class MatchMap {

private:
    int width;                                // cppcheck-suppress unusedStructMember
    int height;                               // cppcheck-suppress unusedStructMember
    //std::vector<std::vector<bool>> game_map;  // cppcheck-suppress unusedStructMember
    std::vector<MapObjectServer> objects;     // cppcheck-suppress unusedStructMember

public:
    MatchMap(int size_x, int size_y);

    int getWidth() const;
    int getHeight() const;
    void setSize(const int width,const int height);

    void add_collision(Tuple position, Tuple dimension, CollisionTypeMap type, int id);
    
    void clear_map();

    bool out_of_map(int position_x, int position_y, int dimension_x, int dimension_y) const;

    bool out_of_map_y(const int y) const;
    bool out_of_map_x(const int x) const;

    bool check_collision(const int x, const int y, CollisionTypeMap &type, int &id) const;
    

    bool check_collision_area( CollisionTypeMap target_type, const int x, const int y
    , const int w, const int h, int &id) const;

    bool check_horizontal_collision(const int x, const int y) const;
    bool check_vertical_collision(const int x, const int y) const;
};


#endif  // MATCH_LOGIC_H
