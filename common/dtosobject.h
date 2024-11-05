#ifndef LIB_DTOS_OBJECT_H
#define LIB_DTOS_OBJECT_H

#include <cstdint>

struct MapPoint {
    uint16_t x;  // cppcheck-suppress unusedStructMember
    uint16_t y;  // cppcheck-suppress unusedStructMember
    MapPoint(uint16_t _x, uint16_t _y): x(_x), y(_y) {}
    MapPoint(): x(0), y(0) {}
};

// Paredes/Plataformas estaticas!
enum BlockType : uint8_t {
    GRASS = 1,
    ROCK = 2  // Algun tipo?
};

struct BlockDTO {
    enum BlockType tipo;   // cppcheck-suppress unusedStructMember
    struct MapPoint pos;   // cppcheck-suppress unusedStructMember
    struct MapPoint size;  // cppcheck-suppress unusedStructMember
};


// Objetos dinamicos!
enum class TypeDynamicObject : uint8_t {
    // Generales
    BOX,
    PROJECTILE,
    BURST,

    HELMET,
    ARMOR,

    // Armas?
    GRANADA,
    BANANA,
    PEW_PEW_LASER,
    LASER_RIFLE,
    AK_47,
    PISTOLA_DE_DUELOS,
    PISTOLA_COWBOY,
    MAGNUM,
    ESCOPETA,
    SNIPER
};


enum ProjectileType : uint8_t {
    GRANADA,
    BANANA,
    PEW_PEW_LASER,
    LASER_RIFLE,
    AK_47,
    PISTOLA_DE_DUELOS,
    PISTOLA_COWBOY,
    MAGNUM,
    ESCOPETA,
    SNIPER,
    BURST
};

struct ProjectileDTO {
    struct MapPoint pos;       // cppcheck-suppress unusedStructMember
    enum ProjectileType tipo;  // cppcheck-suppress unusedStructMember
};

struct DynamicObjDTO {
    struct MapPoint pos;
    TypeDynamicObject type;
    DynamicObjDTO(int x, int y, TypeDynamicObject _type): pos(x, y), type(_type) {}
    DynamicObjDTO() {}
};

enum ObjectType : uint8_t { BOX, ITEM_SPAWN, PLAYER_SPAWN, BLOCK };

struct MapObject {
    struct MapPoint pos;  // cppcheck-suppress unusedStructMember
    ObjectType type;      // cppcheck-suppress unusedStructMember
};


#endif
