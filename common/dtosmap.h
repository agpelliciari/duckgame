#ifndef LIB_DTOS_MAP_H
#define LIB_DTOS_MAP_H

#include <string>
#include <vector>

#include "./dtosobject.h"

// Paredes/Plataformas estaticas!
struct BlockDTO {
    uint8_t texture_id;   // cppcheck-suppress unusedStructMember
    struct MapPoint pos;  // cppcheck-suppress unusedStructMember

    BlockDTO(const coordinate_t x, const coordinate_t y, const uint8_t _tex):
            texture_id(_tex), pos(x, y) {}
};

struct DecorationDTO {
    uint8_t texture_id;   // cppcheck-suppress unusedStructMember
    struct MapPoint pos;  // cppcheck-suppress unusedStructMember
    uint16_t z_ind;       // cppcheck-suppress unusedStructMember

    DecorationDTO(const coordinate_t x, const coordinate_t y, const uint8_t _tex, const uint16_t z):
            texture_id(_tex), pos(x, y), z_ind(z) {}
};


// For server deserial.
struct ObjectsInfo {
    std::vector<struct MapPoint> blocks;         // cppcheck-suppress unusedStructMember
    std::vector<struct MapPoint> boxes;          // cppcheck-suppress unusedStructMember
    std::vector<struct MapPoint> player_spawns;  // cppcheck-suppress unusedStructMember
    std::vector<struct MapPoint> item_spawns;    // cppcheck-suppress unusedStructMember
};


// For sending to client/ through server protocol
struct MapInfo {
    struct MapPoint size;

    uint16_t blocks_z;  // cppcheck-suppress unusedStructMember
    uint16_t boxes_z;   // cppcheck-suppress unusedStructMember

    std::string background;  // cppcheck-suppress unusedStructMember
    std::string boxes_tex;   // cppcheck-suppress unusedStructMember

    std::string map_id;  // cppcheck-suppress unusedStructMember

    std::vector<std::string> textures;              // cppcheck-suppress unusedStructMember
    std::vector<struct BlockDTO> blocks;            // cppcheck-suppress unusedStructMember
    std::vector<struct DecorationDTO> decorations;  // cppcheck-suppress unusedStructMember
    // std::vector<struct MapPoint> boxes;          // cppcheck-suppress unusedStructMember

    MapInfo(const coordinate_t width, const coordinate_t height, const uint16_t block_z,
            const uint16_t box_z):
            size(width, height), blocks_z(block_z), boxes_z(box_z) {}

    MapInfo(): size(0, 0), blocks_z(0), boxes_z(0) {}
};
#endif
