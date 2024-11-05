#include "./serializer.h"

#include <fstream>
#include <iostream>


const char* Serializer::SIZE_X = "size_x";
const char* Serializer::SIZE_Y = "size_y";
const char* Serializer::BACKGROUND = "background";
const char* Serializer::TEXTURES = "textures";
const char* Serializer::BOXES = "boxes";
const char* Serializer::ITEM_SPAWNS = "spawns_item";
const char* Serializer::PLAYER_SPAWNS = "spawns_player";

const int Serializer::POINT_X = 0;
const int Serializer::POINT_Y = 1;

const int Serializer::BLOCK_TEX = 2;


Serializer::Serializer(const uint16_t size_x, const uint16_t size_y): tree(), root(tree.rootref()) {
    root |= ryml::MAP;

    root[Serializer::SIZE_X] << size_x;
    root[Serializer::SIZE_Y] << size_y;
    root[Serializer::BACKGROUND] << 1;

    blocks = root[Serializer::TEXTURES];
    blocks |= ryml::SEQ;

    boxes = root[Serializer::BOXES];
    boxes |= ryml::SEQ;

    item_spawns = root[Serializer::ITEM_SPAWNS];
    item_spawns |= ryml::SEQ;

    player_spawns = root[Serializer::PLAYER_SPAWNS];
    player_spawns |= ryml::SEQ;
}


void Serializer::setBackground(const char* rel_path) {
    std::cout << "SET BACKGROUND " << rel_path << std::endl;
}

void Serializer::setBackground(const std::string& rel_path) { setBackground(rel_path.c_str()); }

void Serializer::addTexture(const uint16_t x, const uint16_t y, BlockTexture type) {
    std::cout << "ADD TEXTURE " << x << y << type << std::endl;
    ryml::NodeRef newitm = blocks.append_child();
    newitm |= ryml::SEQ;
    newitm.append_child() << x;
    newitm.append_child() << y;
    newitm.append_child() << type;
}
void Serializer::addBox(const uint16_t x, const uint16_t y) {
    std::cout << "ADD BOX " << x << y << std::endl;
    ryml::NodeRef newitm = boxes.append_child();
    newitm |= ryml::SEQ;
    newitm.append_child() << x;
    newitm.append_child() << y;
}
void Serializer::addItemSpawn(const uint16_t x, const uint16_t y) {
    std::cout << "ADD Item spawn " << x << y << std::endl;
    ryml::NodeRef newitm = item_spawns.append_child();
    newitm |= ryml::SEQ;
    newitm.append_child() << x;
    newitm.append_child() << y;
}
void Serializer::addPlayerSpawn(const uint16_t x, const uint16_t y) {
    std::cout << "ADD Player spawn " << x << y << std::endl;
    ryml::NodeRef newitm = player_spawns.append_child();
    newitm |= ryml::SEQ;
    newitm.append_child() << x;
    newitm.append_child() << y;
}


void Serializer::save(const char* out) {

    std::cout << "SAVE TO " << out << std::endl;
    std::ofstream file(out, std::ios::binary | std::ios::ate);

    file << tree;
}
void Serializer::save(const std::string& rel_path) { save(rel_path.c_str()); }
