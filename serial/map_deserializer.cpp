#include "./map_deserializer.h"

#include <fstream>
#include <iostream>

#include "./map_serializer.h"
#include "common/core/liberror.h"

MapDeserializer::MapDeserializer(const std::string& src): srcmap(src) {

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

const std::string& MapDeserializer::getMapName() const { return srcmap; }


void MapDeserializer::readSize(struct MapPoint& size) {
    root[MapSerializer::SIZE_X] >> size.x;
    root[MapSerializer::SIZE_Y] >> size.y;
}

void MapDeserializer::readBackground(std::string& background) {
    root[MapSerializer::BACKGROUND] >> background;
}

void MapDeserializer::readBlocksZ(uint16_t& z) { root[MapSerializer::BLOCK_Z] >> z; }

void MapDeserializer::readBoxesZ(uint16_t& z) { root[MapSerializer::BOX_Z] >> z; }

void MapDeserializer::readBoxesTexture(std::string& box_tex) {
    root[MapSerializer::BOX_TEX] >> box_tex;
}


void MapDeserializer::readTextures(std::vector<std::string>& res) {
    ryml::NodeRef textures = root[MapSerializer::TEXTURES];
    if (!textures.is_seq()) {
        std::cout << "NOT FOUND!! TEXTURES SEGMENT!\n";
        return;
    }

    int size = textures.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        std::string tex;
        textures[i] >> tex;
        res.push_back(tex);
    }
}

void MapDeserializer::readDecorations(std::vector<struct DecorationDTO>& res) {
    ryml::NodeRef decorations = root[MapSerializer::DECORATIONS];
    if (!decorations.is_seq()) {
        std::cout << "NOT FOUND!! DECORATIONS SEGMENT!\n";
        return;
    }


    int size = decorations.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        ryml::NodeRef block = decorations[i];
        coordinate_t x;
        coordinate_t y;
        uint8_t tex;
        uint16_t z;


        block[MapSerializer::POINT_X] >> x;
        block[MapSerializer::POINT_Y] >> y;
        block[MapSerializer::BLOCK_TEX] >> tex;
        block[MapSerializer::DECORATION_Z] >> z;

        res.emplace_back(x, y, tex, z);
    }
}


void MapDeserializer::readBlocks(std::vector<struct BlockDTO>& res) {

    // size_t list_id = tree.find_child(tree.root_id(), MapSerializer::TEXTURES);
    // if(!tree.is_seq(list_id)){

    ryml::NodeRef blocks = root[MapSerializer::BLOCKS];
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

        res.emplace_back(x, y, tex);
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


void MapDeserializer::loadMapInfo(struct MapInfo& info) {
    readSize(info.size);

    readBlocksZ(info.blocks_z);
    readBoxesZ(info.boxes_z);

    readBackground(info.background);
    readBoxesTexture(info.boxes_tex);

    readTextures(info.textures);
    readBlocks(info.blocks);
    readDecorations(info.decorations);

    info.map_id = srcmap;
}


void MapDeserializer::loadObjectsInfo(struct ObjectsInfo& info) {
    readPlayerSpawns(info.player_spawns);
    readItemSpawns(info.item_spawns);
    readBoxes(info.boxes);

    // Read blocks .. again? NAA
}
