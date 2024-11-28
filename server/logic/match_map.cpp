#include "match_map.h"

#include <iostream>

MatchMap::MatchMap(int size_x, int size_y): width(size_x), height(size_y) {
    // Segurisimo no es ideal....


    /*game_map.reserve(width);  // Primero la x?

    for (int i = 0; i < width; i++) {
        game_map.emplace_back(height, false);
    }*/
}

int MatchMap::getWidth() const { return width; }
int MatchMap::getHeight() const { return height; }

void MatchMap::add_temp_collision(const int x, const int y) {

    std::cout << "Add temp col at " << x << ", " << y << std::endl;
    // game_map[x][y] = true;
}

void MatchMap::add_collision(Tuple position, Tuple dimension, CollisionTypeMap type, int id) {
    objects.push_back(MapObjectServer(position, dimension, type, id));
}

bool MatchMap::out_of_map_y(const int y) const { return y < 0 || y >= height; }
bool MatchMap::out_of_map_x(const int x) const { return x < 0 || x >= width; }

bool MatchMap::check_collision(const int other_object_x, const int other_object_y, CollisionTypeMap &type, int &id) const {
    if (out_of_map_y(other_object_y) || out_of_map_x(other_object_x) /*||
        game_map[other_object_x][other_object_y]*/) {
        return true;
    }
    for (auto& object: objects) {
        if (other_object_x >= object.map_point.x && other_object_x <= object.map_point.x + object.dimension.x &&
                other_object_y >= object.map_point.y && other_object_y <= object.map_point.y + object.dimension.y) {
            type = object.collision.type;
            id = object.collision.id;
            return true;
        }
    }
    return false;
}

void MatchMap::clear_map() { objects.clear(); }

bool MatchMap::check_horizontal_collision(const int x, const int y) const {
    return !out_of_map_y(y) && (out_of_map_x(x) /*|| game_map[x][y]*/);
}

bool MatchMap::check_vertical_collision(const int x, const int y) const {
    return !out_of_map_x(x) && (out_of_map_y(y) /*|| game_map[x][y]*/);
}

bool MatchMap::out_of_map(int position_x, int position_y, int dimension_x, int dimension_y) const{

    return (position_y <= 0 || position_y + dimension_y >= height -1
            || position_x <= 0 || position_x + dimension_x >= width - 1);


}
