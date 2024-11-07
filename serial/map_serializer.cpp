#include "./map_serializer.h"

#include <fstream>
#include <iostream>


const char* MapSerializer::SIZE_X = "size_x";
const char* MapSerializer::SIZE_Y = "size_y";
const char* MapSerializer::BACKGROUND = "background";
const char* MapSerializer::TEXTURES = "textures";
const char* MapSerializer::BOXES = "boxes";
const char* MapSerializer::ITEM_SPAWNS = "spawns_item";
const char* MapSerializer::PLAYER_SPAWNS = "spawns_player";

const int MapSerializer::POINT_X = 0;
const int MapSerializer::POINT_Y = 1;

const int MapSerializer::BLOCK_TEX = 2;


MapSerializer::MapSerializer(const uint16_t size_x, const uint16_t size_y):
        tree(), root(tree.rootref()) {
    root |= ryml::MAP;

    root[MapSerializer::SIZE_X] << size_x;
    root[MapSerializer::SIZE_Y] << size_y;
    root[MapSerializer::BACKGROUND] << 1;

    blocks = root[MapSerializer::TEXTURES];
    blocks |= ryml::SEQ;

    boxes = root[MapSerializer::BOXES];
    boxes |= ryml::SEQ;

    item_spawns = root[MapSerializer::ITEM_SPAWNS];
    item_spawns |= ryml::SEQ;

    player_spawns = root[MapSerializer::PLAYER_SPAWNS];
    player_spawns |= ryml::SEQ;
}


void MapSerializer::setBackground(const char* rel_path) {
    std::cout << "SET BACKGROUND " << rel_path << std::endl;
}

void MapSerializer::setBackground(const std::string& rel_path) { setBackground(rel_path.c_str()); }

void MapSerializer::addTexture(const uint16_t x, const uint16_t y, BlockTexture type) {
    std::cout << "ADD TEXTURE " << x << y << type << std::endl;
    ryml::NodeRef newitm = blocks.append_child();
    newitm |= ryml::SEQ;
    newitm.append_child() << x;
    newitm.append_child() << y;
    newitm.append_child() << type;
}
void MapSerializer::addBox(const uint16_t x, const uint16_t y) {
    std::cout << "ADD BOX " << x << y << std::endl;
    ryml::NodeRef newitm = boxes.append_child();
    newitm |= ryml::SEQ;
    newitm.append_child() << x;
    newitm.append_child() << y;
}
void MapSerializer::addItemSpawn(const uint16_t x, const uint16_t y) {
    std::cout << "ADD Item spawn " << x << y << std::endl;
    ryml::NodeRef newitm = item_spawns.append_child();
    newitm |= ryml::SEQ;
    newitm.append_child() << x;
    newitm.append_child() << y;
}
void MapSerializer::addPlayerSpawn(const uint16_t x, const uint16_t y) {
    std::cout << "ADD Player spawn " << x << y << std::endl;
    ryml::NodeRef newitm = player_spawns.append_child();
    newitm |= ryml::SEQ;
    newitm.append_child() << x;
    newitm.append_child() << y;
}


void MapSerializer::save(const char* out) {

    std::cout << "SAVE TO " << out << std::endl;
    std::ofstream file(out, std::ios::binary | std::ios::ate);

    file << tree;
}
void MapSerializer::save(const std::string& rel_path) { save(rel_path.c_str()); }
