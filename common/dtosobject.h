#ifndef LIB_DTOS_OBJECT_H
#define LIB_DTOS_OBJECT_H

#include <cstdint>

typedef int coordinate_t;

struct MapPoint {
    coordinate_t x;  // cppcheck-suppress unusedStructMember
    coordinate_t y;  // cppcheck-suppress unusedStructMember
    MapPoint(const coordinate_t _x, const coordinate_t _y): x(_x), y(_y) {}
    MapPoint(): x(0), y(0) {}
};
// Objetos dinamicos!
enum class TypeDynamicObject : uint8_t {
    // Generales
    NONE,
    BOX,
    PROJECTILE,
    GRENADE_PROJECTILE,
    LASER,
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

#endif
