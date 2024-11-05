#include "./deserializer.h"

#include <fstream>
#include <iostream>

#include "./serializer.h"
#include "common/core/liberror.h"


Deserializer::Deserializer(std::string& src) {

    std::ifstream file(src, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Se asume es lo suficientemente small para que entre.
    std::vector<char> map;
    map.reserve(size + 1);
    if (file.read(map.data(), size)) {
        map[size] = 0;
        tree = ryml::parse_in_arena(ryml::csubstr(map.data()));
        root = tree.rootref();
        // std::cout << "CONTENT:\n" << map.data() << "\n----------------------\n";
    } else {
        throw LibError(1, "Failed to read the file to deserialize");
    }
}

struct MapPoint Deserializer::readSize() {

    struct MapPoint size;

    root[Serializer::SIZE_X] >> size.x;
    root[Serializer::SIZE_Y] >> size.y;

    return size;
}
uint8_t Deserializer::readBackground() {
    uint8_t background = 0;

    root[Serializer::BACKGROUND] >> background;

    return background;
}

void Deserializer::readBlocks(std::vector<struct BlockDTO>& res) {

    // size_t list_id = tree.find_child(tree.root_id(), Serializer::TEXTURES);
    // if(!tree.is_seq(list_id)){

    ryml::NodeRef blocks = root[Serializer::TEXTURES];
    if (!blocks.is_seq()) {
        std::cout << "NOT FOUND!! BLOCKS SEGMENT!\n";
        return;
    }


    int size = blocks.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        ryml::NodeRef block = blocks[i];
        uint16_t x;
        uint16_t y;
        uint8_t tex;


        block[Serializer::POINT_X] >> x;
        block[Serializer::POINT_Y] >> y;
        block[Serializer::BLOCK_TEX] >> tex;

        res.emplace_back(x, y, (BlockTexture)tex);
    }
}

void Deserializer::readPoints(ryml::NodeRef& list, std::vector<struct MapPoint>& res) {
    int size = list.num_children();
    res.reserve(size);


    for (int i = 0; i < size; i++) {
        ryml::NodeRef block = list[i];
        struct MapPoint& pos = res.emplace_back(0, 0);

        block[Serializer::POINT_X] >> pos.x;
        block[Serializer::POINT_Y] >> pos.y;
    }
}

void Deserializer::readPlayerSpawns(std::vector<struct MapPoint>& res) {
    ryml::NodeRef list = root[Serializer::PLAYER_SPAWNS];
    if (!list.is_seq()) {
        std::cout << "NOT FOUND!! PLAYER SPAWNS SEGMENT!\n";
        return;
    }
    readPoints(list, res);
}
void Deserializer::readItemSpawns(std::vector<struct MapPoint>& res) {
    ryml::NodeRef list = root[Serializer::ITEM_SPAWNS];
    if (!list.is_seq()) {
        std::cout << "NOT FOUND!! ITEM SPAWNS SEGMENT!\n";
        return;
    }
    readPoints(list, res);
}

void Deserializer::readBoxes(std::vector<struct MapPoint>& res) {
    ryml::NodeRef list = root[Serializer::BOXES];
    if (!list.is_seq()) {
        std::cout << "NOT FOUND!! BOXES SEGMENT!\n";
        return;
    }

    readPoints(list, res);
}

void Deserializer::dosome() {
    struct MapPoint size = readSize();
    uint8_t bk = readBackground();

    std::cout << "MAP SIZE IS " << size.x << " , " << size.y << " BACKGROUND: " << (int)bk
              << std::endl;

    std::vector<BlockDTO> blocks;

    readBlocks(blocks);

    std::cout << "Block count " << blocks.size() << std::endl;

    for (const BlockDTO& block: blocks) {
        std::cout << "Block at " << block.pos.x << " , " << block.pos.y
                  << " Tex: " << (int)block.texture << std::endl;
    }
}
