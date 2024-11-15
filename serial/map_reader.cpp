#include "./map_reader.h"

#include <fstream>
#include <iostream>

#include "common/core/liberror.h"







const char* MapReader::SIZE_X = "size_x";
const char* MapReader::SIZE_Y = "size_y";
const char* MapReader::BACKGROUND = "background";
const char* MapReader::TEXTURES = "textures";

const char* MapReader::BLOCKS = "blocks";
const char* MapReader::DECORATIONS = "decorations";

const char* MapReader::BOXES = "boxes";
const char* MapReader::ITEM_SPAWNS = "spawns_item";
const char* MapReader::PLAYER_SPAWNS = "spawns_player";

const char* MapReader::POINT_X = "x";  //= 0;
const char* MapReader::POINT_Y = "y";  //= 1;

const char* MapReader::BLOCK_TEX = "ind_tex";  //= 2;

const char* MapReader::BLOCK_Z = "blocks_z";
const char* MapReader::BOX_Z = "boxes_z";
const char* MapReader::BOX_TEX = "box_texture";

const char* MapReader::DECORATION_Z = "z_ind";







MapReader::MapReader(const std::string& src) {

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

void MapReader::readSize(struct MapPoint& size) {
    root[MapReader::SIZE_X] >> size.x;
    root[MapReader::SIZE_Y] >> size.y;
}

void MapReader::readBackground(std::string& background) {
    root[MapReader::BACKGROUND] >> background;
}

void MapReader::readBlocksZ(uint16_t& z) { root[MapReader::BLOCK_Z] >> z; }

void MapReader::readBoxesZ(uint16_t& z) { root[MapReader::BOX_Z] >> z; }

void MapReader::readBoxesTexture(std::string& box_tex) {
    root[MapReader::BOX_TEX] >> box_tex;
}

void MapReader::readTextures(std::vector<std::string>& res) {
    ryml::NodeRef textures = root[MapReader::TEXTURES];
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

void MapReader::readItemPosition(read_item_t& item, struct MapPoint& pos){
    item[MapReader::POINT_X] >> pos.x;
    item[MapReader::POINT_Y] >> pos.y;
}

void MapReader::readItemZInd(read_item_t& item, uint16_t& out){
    item[MapReader::DECORATION_Z] >> out;
}

void MapReader::readItemTexture(read_item_t& item, uint8_t& out){
    item[MapReader::BLOCK_TEX] >> out;
}

void MapReader::readPoints(read_seq_t& list, std::vector<struct MapPoint>& res) {
    int size = list.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        readItemPosition(list[i], res.emplace_back(0, 0));
    }
}

read_seq_t& MapReader::getBoxes() {
    read_seq_t& list = root[MapReader::BOXES];
    if (list.is_seq()) {
         return list;
    }
    throw LibError(1, "Did not find boxes segment");
}

read_seq_t& MapReader::getItemSpawns() {
    read_seq_t& list = root[MapReader::ITEM_SPAWNS];
    if (list.is_seq()) {
         return list;
    }
    throw LibError(1, "Did not find item spawns segment");
}

read_seq_t& MapReader::getPlayerSpawns() {
    read_seq_t& list = root[MapReader::PLAYER_SPAWNS];
    if (list.is_seq()) {
         return list;
    }
    throw LibError(1, "Did not find player spawns segment");
}


read_seq_t& MapReader::getBlocks() {
    read_seq_t& list = root[MapReader::BLOCKS];
    if (list.is_seq()) {
         return list;
    }
    throw LibError(1, "Did not find player blocks segment");
}

read_seq_t& MapReader::getDecorations() {
    read_seq_t& list = root[MapReader::DECORATIONS];
    if (list.is_seq()) {
         return list;
    }
    throw LibError(1, "Did not find player blocks segment");
}

