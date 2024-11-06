#ifndef LIB_DTOS_MAP_H
#define LIB_DTOS_MAP_H

#include <string>
#include <vector>

#include "./dtosobject.h"

// Paredes/Plataformas estaticas!
enum BlockTexture : uint8_t {
    GRASS = 1,
    ROCK = 2  // Algun tipo?
};

struct BlockDTO {
    enum BlockTexture texture;  // cppcheck-suppress unusedStructMember
    struct MapPoint pos;        // cppcheck-suppress unusedStructMember
    struct MapPoint size;       // cppcheck-suppress unusedStructMember

    BlockDTO(const coordinate_t x, const coordinate_t y, const BlockTexture _tex):
            texture(_tex), pos(x, y), size(1, 1) {}
};

struct MapInfo {
    std::string mapname;
    struct MapPoint size;
    uint8_t bk;
    std::vector<struct BlockDTO> blocks;         // cppcheck-suppress unusedStructMember
    std::vector<struct MapPoint> boxes;          // cppcheck-suppress unusedStructMember
    std::vector<struct MapPoint> spawns_player;  // cppcheck-suppress unusedStructMember
    std::vector<struct MapPoint> spawns_items;   // cppcheck-suppress unusedStructMember

    MapInfo(const std::string& name, const struct MapPoint _size, uint8_t _bk):
            mapname(name), size(_size), bk(_bk) {}
};


enum ObjectType : uint8_t { BOX, ITEM_SPAWN, PLAYER_SPAWN, BLOCK };
struct MapObject {
    struct MapPoint pos;  // cppcheck-suppress unusedStructMember
    ObjectType type;      // cppcheck-suppress unusedStructMember
};


#endif
