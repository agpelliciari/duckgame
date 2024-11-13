#include "./map_serializer.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>


static const char* DEF_MAP_BK = "default.png";
static const char* DEF_BOX_TEX = "default_tex.png";

const char* MapSerializer::SIZE_X = "size_x";
const char* MapSerializer::SIZE_Y = "size_y";
const char* MapSerializer::BACKGROUND = "background";
const char* MapSerializer::TEXTURES = "textures";

const char* MapSerializer::BLOCKS = "blocks";
const char* MapSerializer::DECORATIONS = "decorations";

const char* MapSerializer::BOXES = "boxes";
const char* MapSerializer::ITEM_SPAWNS = "spawns_item";
const char* MapSerializer::PLAYER_SPAWNS = "spawns_player";

const char* MapSerializer::POINT_X = "x";  //= 0;
const char* MapSerializer::POINT_Y = "y";  //= 1;

const char* MapSerializer::BLOCK_TEX = "ind_tex";  //= 2;

const char* MapSerializer::BLOCK_Z = "blocks_z";
const char* MapSerializer::BOX_Z = "boxes_z";
const char* MapSerializer::BOX_TEX = "box_texture";

const char* MapSerializer::DECORATION_Z = "z_ind";


MapSerializer::MapSerializer(const uint16_t size_x, const uint16_t size_y):
        count_textures(0),
        z_ind_block(0),
        z_ind_box(1),
        box_tex(DEF_BOX_TEX),
        tree(),
        root(tree.rootref()) {
    root |= ryml::MAP;

    root[MapSerializer::SIZE_X] << size_x;
    root[MapSerializer::SIZE_Y] << size_y;
    root[MapSerializer::BACKGROUND] << DEF_MAP_BK;

    root[MapSerializer::BLOCK_Z] << z_ind_block;
    root[MapSerializer::BOX_Z] << z_ind_box;
    root[MapSerializer::BOX_TEX] << box_tex;

    ryml::NodeRef textures = root[MapSerializer::TEXTURES];
    textures |= ryml::SEQ;

    blocks = root[MapSerializer::BLOCKS];
    blocks |= ryml::SEQ;

    decorations = root[MapSerializer::DECORATIONS];
    decorations |= ryml::SEQ;

    boxes = root[MapSerializer::BOXES];
    boxes |= ryml::SEQ;

    item_spawns = root[MapSerializer::ITEM_SPAWNS];
    item_spawns |= ryml::SEQ;

    player_spawns = root[MapSerializer::PLAYER_SPAWNS];
    player_spawns |= ryml::SEQ;
}

uint8_t MapSerializer::mapTexture(const std::string& tex_name) {
    auto res = map_textures.insert(type_map_textures::value_type(tex_name, count_textures));
    if (!res.second) {  // Ya existia el valor. Por lo cual retorna el valor existente.
        return res.first->second;
    }

    // No existia, retorna el count actual, id de la texture. Y aumenta.
    return count_textures++;
}


void MapSerializer::setBackground(const char* rel_path) {
    std::cout << "SET BACKGROUND " << rel_path << std::endl;
    root[MapSerializer::BACKGROUND] << DEF_MAP_BK;
}

void MapSerializer::setBackground(const std::string& rel_path) { setBackground(rel_path.c_str()); }

void MapSerializer::addBlock(const uint16_t x, const uint16_t y, const std::string& name) {
    std::cout << "ADD BLOCK " << x << y << name << std::endl;
    ryml::NodeRef newitm = blocks.append_child();
    newitm |= ryml::MAP;
    newitm[MapSerializer::POINT_X] << x;
    newitm[MapSerializer::POINT_Y] << y;
    newitm[MapSerializer::BLOCK_TEX] << mapTexture(name);
}
void MapSerializer::addBlock(const uint16_t x, const uint16_t y, const uint16_t z,
                             const std::string& name) {
    z_ind_block = z;  // Podriamos solo modificar de ser necesario... pero naa!
    addBlock(x, y, name);
}
void MapSerializer::addDecoration(const uint16_t x, const uint16_t y, const uint16_t z,
                                  const std::string& name) {
    std::cout << "ADD DECORATION " << x << y << "z: " << z << " " << name << std::endl;
    ryml::NodeRef newitm = decorations.append_child();
    newitm |= ryml::MAP;
    newitm[MapSerializer::POINT_X] << x;
    newitm[MapSerializer::POINT_Y] << y;
    newitm[MapSerializer::DECORATION_Z] << z;
    newitm[MapSerializer::BLOCK_TEX] << mapTexture(name);
}

void MapSerializer::addBox(const uint16_t x, const uint16_t y) {
    std::cout << "ADD BOX " << x << y << std::endl;
    ryml::NodeRef newitm = boxes.append_child();
    newitm |= ryml::MAP;
    newitm[MapSerializer::POINT_X] << x;
    newitm[MapSerializer::POINT_Y] << y;
}
void MapSerializer::addBox(const uint16_t x, const uint16_t y, const uint16_t z,
                           const std::string& name) {
    z_ind_box = z;   // Podriamos solo modificar de ser necesario... pero naa!
    box_tex = name;  // Podriamos solo modificar de ser necesario... pero naa!
    addBox(x, y);
}


void MapSerializer::addItemSpawn(const uint16_t x, const uint16_t y, const std::string& name) {
    addBlock(x, y, name);  // Add block to represent in map

    std::cout << "ADD Item spawn " << x << y << std::endl;
    ryml::NodeRef newitm = item_spawns.append_child();
    newitm |= ryml::MAP;
    newitm[MapSerializer::POINT_X] << x;
    newitm[MapSerializer::POINT_Y] << y;
}


void MapSerializer::addItemSpawn(const uint16_t x, const uint16_t y, const uint16_t z,
                                 const std::string& name) {
    z_ind_block = z;  // Podriamos solo modificar de ser necesario... pero naa!
    addItemSpawn(x, y, name);
}


void MapSerializer::addPlayerSpawn(const uint16_t x, const uint16_t y, const std::string& name) {
    addBlock(x, y, name);  // Add block to represent in map

    std::cout << "ADD Player spawn " << x << y << std::endl;
    ryml::NodeRef newitm = player_spawns.append_child();
    newitm |= ryml::MAP;
    newitm[MapSerializer::POINT_X] << x;
    newitm[MapSerializer::POINT_Y] << y;
}

void MapSerializer::addPlayerSpawn(const uint16_t x, const uint16_t y, const uint16_t z,
                                   const std::string& name) {
    z_ind_block = z;  // Podriamos solo modificar de ser necesario... pero naa!
    addPlayerSpawn(x, y, name);
}

struct less_than_id {
    inline bool operator()(const PairTexture& pair1, const PairTexture& pair2) {
        return (pair1.id < pair2.id);
    }
};

void MapSerializer::save(const char* out) {

    std::cout << "SAVE TO " << out << std::endl;
    std::ofstream file(out, std::ios::binary | std::ios::ate);

    root[MapSerializer::BLOCK_Z] << z_ind_block;
    root[MapSerializer::BOX_Z] << z_ind_box;
    root[MapSerializer::BOX_TEX] << box_tex;

    ryml::NodeRef textures = root[MapSerializer::TEXTURES];

    std::vector<PairTexture> vec_tex;
    vec_tex.reserve(map_textures.size());
    for (auto it = map_textures.begin(); it != map_textures.end(); it++) {
        vec_tex.emplace_back(it->second, it->first);
    }

    std::sort(vec_tex.begin(), vec_tex.end(), less_than_id());

    for (const PairTexture& pair: vec_tex) {
        textures.append_child() << pair.tex;
    }

    file << tree;
}
void MapSerializer::save(const std::string& rel_path) { save(rel_path.c_str()); }
