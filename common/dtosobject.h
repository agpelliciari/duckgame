#ifndef LIB_DTOS_OBJECT_H
#define LIB_DTOS_OBJECT_H

#include <cstdint>


// Paredes/Plataformas estaticas!
enum BlockType : uint8_t {
    GRASS = 1,
    ROCK = 2  // Algun tipo?
};

struct BlockDTO {
    uint8_t pos_x;
    uint8_t pos_y;
    enum BlockType tipo;
    uint8_t size_x;  // Haria falta?! puede que sea mejor si.
    uint8_t size_y;
} __attribute__((packed));


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

struct ProjectileDTO{
    uint8_t pos_x;
    uint8_t pos_y;
    enum ProjectileType tipo;
}

struct DynamicObjDTO {
    int pos_x;
    int pos_y;
    TypeDynamicObject type;
    DynamicObjDTO(int x, int y, TypeDynamicObject _type): pos_x(x), pos_y(y), type(_type) {}
    DynamicObjDTO() {}
};

#endif
