#include "./map_deserializer.h"

#include <fstream>
#include <iostream>

#include "./map_serializer.h"
#include "common/core/liberror.h"


MapDeserializer::MapDeserializer(const std::string& src) {

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

struct MapPoint MapDeserializer::readSize() {

    struct MapPoint size;

    root[MapSerializer::SIZE_X] >> size.x;
    root[MapSerializer::SIZE_Y] >> size.y;

    return size;
}
uint8_t MapDeserializer::readBackground() {
    uint8_t background = 0;

    root[MapSerializer::BACKGROUND] >> background;

    return background;
}

void MapDeserializer::readBlocks(std::vector<struct BlockDTO>& res) {

    // size_t list_id = tree.find_child(tree.root_id(), MapSerializer::TEXTURES);
    // if(!tree.is_seq(list_id)){

    ryml::NodeRef blocks = root[MapSerializer::TEXTURES];
    if (!blocks.is_seq()) {
        std::cout << "NOT FOUND!! BLOCKS SEGMENT!\n";
        return;
    }


    int size = blocks.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        ryml::NodeRef block = blocks[i];
        coordinate_t x;
        coordinate_t y;
        uint8_t tex;


        block[MapSerializer::POINT_X] >> x;
        block[MapSerializer::POINT_Y] >> y;
        block[MapSerializer::BLOCK_TEX] >> tex;

        res.emplace_back(x, y, (BlockTexture)tex);
    }
}

void MapDeserializer::readPoints(ryml::NodeRef& list, std::vector<struct MapPoint>& res) {
    int size = list.num_children();
    res.reserve(size);


    for (int i = 0; i < size; i++) {
        ryml::NodeRef block = list[i];
        struct MapPoint& pos = res.emplace_back(0, 0);

        block[MapSerializer::POINT_X] >> pos.x;
        block[MapSerializer::POINT_Y] >> pos.y;
    }
}

void MapDeserializer::readPlayerSpawns(std::vector<struct MapPoint>& res) {
    ryml::NodeRef list = root[MapSerializer::PLAYER_SPAWNS];
    if (!list.is_seq()) {
        std::cout << "NOT FOUND!! PLAYER SPAWNS SEGMENT!\n";
        return;
    }
    readPoints(list, res);
}
void MapDeserializer::readItemSpawns(std::vector<struct MapPoint>& res) {
    ryml::NodeRef list = root[MapSerializer::ITEM_SPAWNS];
    if (!list.is_seq()) {
        std::cout << "NOT FOUND!! ITEM SPAWNS SEGMENT!\n";
        return;
    }
    readPoints(list, res);
}

void MapDeserializer::readBoxes(std::vector<struct MapPoint>& res) {
    ryml::NodeRef list = root[MapSerializer::BOXES];
    if (!list.is_seq()) {
        std::cout << "NOT FOUND!! BOXES SEGMENT!\n";
        return;
    }

    readPoints(list, res);
}

void MapDeserializer::dosome() {
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
