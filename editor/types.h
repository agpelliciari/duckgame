#ifndef TYPES_H
#define TYPES_H

#include <QPixmap>
#include <string>

enum MapObjectType {
    Background,
    Block,
    SpawnPlayer,
    SpawnWeapon,
    Box,
    Decoration,
    Empty
};

struct Texture {
    std::string name;
    std::string source;
    MapObjectType mapObjectType;
    QPixmap pixelMap;
};

#endif