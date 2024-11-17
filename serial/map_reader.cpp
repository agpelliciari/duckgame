#include "./map_reader.h"

#include <fstream>
#include <iostream>
#include <errno.h>

#include "common/serialerror.h"
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







MapReader::MapReader(const std::string& src){ //:root_id(0) {

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
        //root_id = tree.root_id();
        // std::cout << "CONTENT:\n" << map.data() << "\n----------------------\n";
    } else {
        throw LibError(errno, "Failed to read the file to deserialize ");
    }
}

void MapReader::assertIsMap(read_item_t& item){
     if((!item.is_seed()) && item.is_map()){
         return;
     }
     throw SerialError("Required map item, was not a map!");
}

bool MapReader::checkIsSeq(read_item_t& item){ 
     return (!item.is_seed()) && item.is_seq();
     //return item.id() != -1 && item.is_seq();
}


bool MapReader::checkInvalid(read_item_t& item){
     return item.invalid() || item.is_seed();     
}

void MapReader::readSize(struct MapPoint& size) {
    read_item_t width = root[MapReader::SIZE_X];
    if(checkInvalid(width)){
         throw SerialError("Failed read of size, did not find width key");
    }
    
    read_item_t height = root[MapReader::SIZE_Y];
    if(checkInvalid(height)){
         throw SerialError("Failed read of size, did not find height key");
    }
    
    width >> size.x;
    height >> size.y;
}

void MapReader::readBackground(std::string& background) {
    read_item_t bk = root[MapReader::BACKGROUND];
    if(checkInvalid(bk)){
       throw SerialError("Failed read of background, did not find required key");    
    }
    bk >> background;
}

void MapReader::readBlocksZ(uint16_t& z) { 
    read_item_t vl = root[MapReader::BLOCK_Z];
    if(checkInvalid(vl)){
       throw SerialError("Failed read of blocks z, did not find required key");
    }
    vl >> z;
}

void MapReader::readBoxesZ(uint16_t& z) {
    read_item_t vl = root[MapReader::BOX_Z];
    if(checkInvalid(vl)){
       throw SerialError("Failed read of boxes z, did not find required key");
       return;
    }
    vl >> z;
}

void MapReader::readBoxesTexture(std::string& box_tex) {
    read_item_t vl = root[MapReader::BOX_TEX];
    if(checkInvalid(vl)){
       throw SerialError("Failed read of boxes texture, did not find required key");
    }
    vl >> box_tex;
}

void MapReader::readTextures(std::vector<std::string>& res) {
    // Como podria ser para el caso de trabajar con ids
    //size_t textures_id = tree.find_child(root_id, MapReader::TEXTURES);
    //if (list_id == -1 && !tree.is_seq(textures_id)) {
    //    std::cout << "NOT FOUND!! TEXTURES SEGMENT!\n";
    //    return;
    //}
    
    ryml::NodeRef textures = root[MapReader::TEXTURES];
    if(checkIsSeq(textures)){
        int size = textures.num_children();
        res.reserve(size);

        for (int i = 0; i < size; i++) {
            std::string tex;
            textures[i] >> tex;
            res.push_back(tex);
        }
        return;
    }
    throw SerialError("Did not find textures segment!");
}

void MapReader::readItemPosition(read_item_t& item, struct MapPoint& pos){
    ryml::NodeRef x = item[MapReader::POINT_X];
    if(checkInvalid(x)){
         throw SerialError("Failed read of item position, did not have x key ");
    }
    
    ryml::NodeRef y = item[MapReader::POINT_Y];
    if(checkInvalid(y)){
         throw SerialError("Failed read of item position, did not have y key ");
    }
    x >> pos.x;
    y >> pos.y;
}

void MapReader::readItemZInd(read_item_t& item, uint16_t& out){
    ryml::NodeRef z = item[MapReader::DECORATION_Z];
    if(checkInvalid(z)){
        throw SerialError("Failed read of item z index, did not have required key ");    
    }
    z >> out;
}

void MapReader::readItemTexture(read_item_t& item, uint8_t& out){
    ryml::NodeRef z = item[MapReader::MapReader::BLOCK_TEX];
    if(checkInvalid(z)){
        throw SerialError("Failed read of item texture, did not have required key");    
    }
    z >> out;
}

void MapReader::readPoints(read_seq_t list, std::vector<struct MapPoint>& res) {
    int size = list.num_children();
    res.reserve(size);

    for (int i = 0; i < size; i++) {
        read_item_t item = list[i];
        assertIsMap(item);        
        readItemPosition(item, res.emplace_back(0, 0));
    }
}

read_seq_t MapReader::getBoxes() {
    read_seq_t list = root[MapReader::BOXES];
    if (checkIsSeq(list)) {
         return list;
    }
    throw SerialError("Did not find boxes segment");
}

read_seq_t MapReader::getItemSpawns() {
    read_seq_t list = root[MapReader::ITEM_SPAWNS];
    if (checkIsSeq(list)) {
         return list;
    }
    throw SerialError("Did not find item spawns segment");
}

read_seq_t MapReader::getPlayerSpawns() {
    read_seq_t list = root[MapReader::PLAYER_SPAWNS];
    if (checkIsSeq(list)) {
         return list;
    }
    throw SerialError("Did not find player spawns segment");
}


read_seq_t MapReader::getBlocks() {
    read_seq_t list = root[MapReader::BLOCKS];
    if (checkIsSeq(list)) {
         return list;
    }
    throw SerialError("Did not find player blocks segment");
}

read_seq_t MapReader::getDecorations() {
    read_seq_t list = root[MapReader::DECORATIONS];
    if (checkIsSeq(list)) {
         return list;
    }
    throw SerialError("Did not find player blocks segment");
}

