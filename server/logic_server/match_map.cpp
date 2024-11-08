#include "match_map.h"

#include <iostream>

MatchMap::MatchMap(int size_x, int size_y): width(size_x), height(size_y) {
    // Segurisimo no es ideal....


    game_map.reserve(height);  // Primero la y?

    for (int i = 0; i < height; i++) {
        // std::vector<bool>& col =
        game_map.emplace_back(width, false);
    }

    // defino un mapa vacio con paredes y pisos
    // tal que asi:
    //
    //    1 1 1 1 1 1 1 1 1 1
    //    1 0 0 0 0 0 0 0 0 1
    //    1 0 0 0 0 0 0 0 0 1
    //    1 0 0 0 0 0 0 0 0 1
    //    1 0 0 0 0 0 0 0 0 1
    //    1 1 1 1 1 1 1 1 1 1
    for (int i = 0; i < width; i++) {
        game_map[0][i] = true;
        game_map[height - 1][i] = true;
    }

    for (int i = 0; i < height; i++) {
        game_map[i][0] = true;
        game_map[i][width - 1] = true;
    }
}

int MatchMap::getWidth() const { return width; }
int MatchMap::getHeight() const { return height; }

void MatchMap::add_temp_collision(const int x, const int y) {

    std::cout << "Add temp col at " << x << ", " << y << std::endl;
    // game_map[x][y] = true;
}

void MatchMap::add_collision(Tuple position, Tuple dimension) {
    objects.push_back(MapObjectServer(position, dimension));
}

bool MatchMap::out_of_map_y(const int y) const { return y < 0 || y >= height; }
bool MatchMap::out_of_map_x(const int x) const { return x < 0 || x >= width; }

bool MatchMap::check_collision(const int other_object_x, const int other_object_y) const {
    if (game_map[other_object_x][other_object_y]) {
        return true;
    }
    for (auto &object : objects) {
        if (object.map_point.x == other_object_x
            && object.map_point.y == other_object_y ) {
            return true;
        }
        if (object.map_point.x + object.dimension.x == other_object_x
            && object.map_point.y == other_object_y){
            return true;
        }
        if (object.map_point.x == other_object_x
            && object.map_point.y + object.dimension.y == other_object_y){
            return true;
        }
        if (object.map_point.x + object.dimension.x == other_object_x
            && object.map_point.y + object.dimension.y == other_object_y){
            return true;
        }
    }
    return false;
}

void MatchMap::clear_objects(){
    objects.clear();
}

bool MatchMap::check_horizontal_collision(const int x, const int y) const {
    return !out_of_map_y(y) && (out_of_map_x(x) || game_map[y][x]);
}

bool MatchMap::check_vertical_collision(const int x, const int y) const {
    return !out_of_map_x(x) && (out_of_map_y(y) || game_map[y][x]);
}
