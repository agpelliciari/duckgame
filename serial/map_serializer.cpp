#include "./map_serializer.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>


static const char* DEF_MAP_BK = "default.png";
static const char* DEF_BOX_TEX = "default_tex.png";



MapSerializer::MapSerializer(const uint16_t size_x, const uint16_t size_y):
        count_textures(0),
        z_ind_block(0),
        z_ind_box(1),
        box_tex(DEF_BOX_TEX),
        tree(),
        root(tree.rootref()) {
    root |= ryml::MAP;

    root[MapReader::SIZE_X] << size_x;
    root[MapReader::SIZE_Y] << size_y;
    root[MapReader::BACKGROUND] << DEF_MAP_BK;

    root[MapReader::BLOCK_Z] << z_ind_block;
    root[MapReader::BOX_Z] << z_ind_box;
    root[MapReader::BOX_TEX] << box_tex;

    ryml::NodeRef textures = root[MapReader::TEXTURES];
    textures |= ryml::SEQ;

    blocks = root[MapReader::BLOCKS];
    blocks |= ryml::SEQ;

    decorations = root[MapReader::DECORATIONS];
    decorations |= ryml::SEQ;

    boxes = root[MapReader::BOXES];
    boxes |= ryml::SEQ;

    item_spawns = root[MapReader::ITEM_SPAWNS];
    item_spawns |= ryml::SEQ;

    player_spawns = root[MapReader::PLAYER_SPAWNS];
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
    root[MapReader::BACKGROUND] << rel_path;
}

void MapSerializer::setBackground(const std::string& rel_path) { setBackground(rel_path.c_str()); }

void MapSerializer::addBlock(const uint16_t x, const uint16_t y, const std::string& name) {
    std::cout << "ADD BLOCK " << x << y << name << std::endl;
    ryml::NodeRef newitm = blocks.append_child();
    newitm |= ryml::MAP;
    newitm[MapReader::POINT_X] << x;
    newitm[MapReader::POINT_Y] << y;
    newitm[MapReader::BLOCK_TEX] << mapTexture(name);
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
    newitm[MapReader::POINT_X] << x;
    newitm[MapReader::POINT_Y] << y;
    newitm[MapReader::DECORATION_Z] << z;
    newitm[MapReader::BLOCK_TEX] << mapTexture(name);
}

void MapSerializer::addBox(const uint16_t x, const uint16_t y) {
    std::cout << "ADD BOX " << x << y << std::endl;
    ryml::NodeRef newitm = boxes.append_child();
    newitm |= ryml::MAP;
    newitm[MapReader::POINT_X] << x;
    newitm[MapReader::POINT_Y] << y;
}
void MapSerializer::addBox(const uint16_t x, const uint16_t y, const uint16_t z,
                           const std::string& name) {
    z_ind_box = z;   // Podriamos solo modificar de ser necesario... pero naa!
    box_tex = name;  // Podriamos solo modificar de ser necesario... pero naa!
    addBox(x, y);
}


void MapSerializer::addItemSpawn(const uint16_t x, const uint16_t y, const std::string& name) {
    std::cout << "ADD Item spawn " << x << y << std::endl;
    ryml::NodeRef newitm = item_spawns.append_child();
    newitm |= ryml::MAP;
    newitm[MapReader::POINT_X] << x;
    newitm[MapReader::POINT_Y] << y;
    newitm[MapReader::BLOCK_TEX] << mapTexture(name);
}


void MapSerializer::addItemSpawn(const uint16_t x, const uint16_t y, const uint16_t z,
                                 const std::string& name) {
    z_ind_block = z;  // Podriamos solo modificar de ser necesario... pero naa!
    addItemSpawn(x, y, name);
}


void MapSerializer::addPlayerSpawn(const uint16_t x, const uint16_t y, const std::string& name) {
    std::cout << "ADD Player spawn " << x << y << std::endl;
    ryml::NodeRef newitm = player_spawns.append_child();
    newitm |= ryml::MAP;
    newitm[MapReader::POINT_X] << x;
    newitm[MapReader::POINT_Y] << y;
    newitm[MapReader::BLOCK_TEX] << mapTexture(name);
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

    root[MapReader::BLOCK_Z] << z_ind_block;
    root[MapReader::BOX_Z] << z_ind_box;
    root[MapReader::BOX_TEX] << box_tex;

    ryml::NodeRef textures = root[MapReader::TEXTURES];

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
