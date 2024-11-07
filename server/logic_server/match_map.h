#ifndef MATCH_MAP_H
#define MATCH_MAP_H

#include <vector>
#include "map_object.h"
#include "tuple.h"
#include "physical_object.h"

class MatchMap {

private:
    int width;
    int height;
    std::vector<std::vector<bool>> game_map;  // cppcheck-suppress unusedStructMember
    std::vector<MapObjectServer> objects;

public:
    MatchMap(int size_x, int size_y);

    void add_temp_collision(const int x, const int y);

    void add_collision(Tuple position, Tuple dimension);
    void clear_objects();

    int getWidth() const;
    int getHeight() const;

    bool out_of_map_y(const int y) const;
    bool out_of_map_x(const int x) const;

    bool check_collision(const int x, const int y) const;
    bool check_horizontal_collision(const int x, const int y) const;
    bool check_vertical_collision(const int x, const int y) const;
};


#endif  // MATCH_LOGIC_H
