#ifndef LIB_MAP_SERIALIZER_H
#define LIB_MAP_SERIALIZER_H

#include <atomic>
#include <cstdint>
#include <string>

// Tomado de https://github.com/biojppm/rapidyaml/blob/master/samples/quickstart.cpp
#if defined(RYML_SINGLE_HEADER)  // using the single header directly in the executable
#define RYML_SINGLE_HDR_DEFINE_NOW
#include <ryml_all.hpp>
#elif defined(RYML_SINGLE_HEADER_LIB)  // using the single header from a library
#include <ryml_all.hpp>
#else
#include <ryml.hpp>
// <ryml_std.hpp> is needed if interop with std containers is
// desired; ryml itself does not use any STL container.
// For this sample, we will be using std interop, so...
#include <c4/format.hpp>  // needed for the examples below
#include <ryml_std.hpp>   // optional header, provided for std:: interop
#endif

#include <map>

#include "common/dtosmap.h"

typedef std::map<std::string, int> type_map_textures;


class PairTexture {
public:
    int id;           // cppcheck-suppress unusedStructMember
    const char* tex;  // cppcheck-suppress unusedStructMember
    PairTexture(int _id, const std::string& _tex): id(_id), tex(_tex.c_str()) {}

    PairTexture(const PairTexture& _other): id(_other.id), tex(_other.tex) {}
    PairTexture& operator=(const PairTexture& other) {
        id = other.id;
        tex = other.tex;
        return *this;
    }

    PairTexture(PairTexture&& _other): id(_other.id), tex(_other.tex) {}
    PairTexture& operator=(PairTexture&& other) {
        id = other.id;
        tex = other.tex;
        return *this;
    }
};

class MapSerializer {
public:
    static const char* SIZE_X;       // cppcheck-suppress unusedStructMember
    static const char* SIZE_Y;       // cppcheck-suppress unusedStructMember
    static const char* BACKGROUND;   // cppcheck-suppress unusedStructMember
    static const char* TEXTURES;     // cppcheck-suppress unusedStructMember
    static const char* BLOCKS;       // cppcheck-suppress unusedStructMember
    static const char* DECORATIONS;  // cppcheck-suppress unusedStructMember
    static const char* BOXES;        // cppcheck-suppress unusedStructMember

    static const char* ITEM_SPAWNS;    // cppcheck-suppress unusedStructMember
    static const char* PLAYER_SPAWNS;  // cppcheck-suppress unusedStructMember


    static const char* POINT_X;  // cppcheck-suppress unusedStructMember
    static const char* POINT_Y;  // cppcheck-suppress unusedStructMember

    static const char* BLOCK_Z;  // cppcheck-suppress unusedStructMember
    static const char* BOX_Z;    // cppcheck-suppress unusedStructMember
    static const char* BOX_TEX;  // cppcheck-suppress unusedStructMember

    static const char* BLOCK_TEX;  // cppcheck-suppress unusedStructMember

    static const char* DECORATION_Z;  // cppcheck-suppress unusedStructMember

protected:
    int count_textures;    // cppcheck-suppress unusedStructMember
    uint16_t z_ind_block;  // cppcheck-suppress unusedStructMember
    uint16_t z_ind_box;    // cppcheck-suppress unusedStructMember
    std::string box_tex;   // cppcheck-suppress unusedStructMember

    ryml::Tree tree;
    ryml::NodeRef root;
    ryml::NodeRef blocks;
    ryml::NodeRef boxes;
    ryml::NodeRef item_spawns;
    ryml::NodeRef player_spawns;
    ryml::NodeRef decorations;

    type_map_textures map_textures;  // cppcheck-suppress unusedStructMember

    uint8_t mapTexture(const std::string& tex_name);

public:
    explicit MapSerializer(const uint16_t width, const uint16_t height);
    // Asumamos por ahora que no se quiere permitir copias..
    MapSerializer(const MapSerializer&) = delete;
    MapSerializer& operator=(const MapSerializer&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    MapSerializer(MapSerializer&&) = delete;
    MapSerializer& operator=(MapSerializer&&) = delete;


    void setBackground(const char* rel_path);
    void setBackground(const std::string& rel_path);

    // Default... como z index probablemente sea el mismo.. En todos
    void addBlock(const uint16_t x, const uint16_t y, const std::string& name);
    void addBlock(const uint16_t x, const uint16_t y, const uint16_t z, const std::string& name);

    void addDecoration(const uint16_t x, const uint16_t y, const uint16_t z,
                       const std::string& name);

    void addBox(const uint16_t x, const uint16_t y);
    void addBox(const uint16_t x, const uint16_t y, const uint16_t z, const std::string& name);


    void addItemSpawn(const uint16_t x, const uint16_t y, const std::string& name);
    void addItemSpawn(const uint16_t x, const uint16_t y, const uint16_t z,
                      const std::string& name);

    void addPlayerSpawn(const uint16_t x, const uint16_t y, const std::string& name);
    void addPlayerSpawn(const uint16_t x, const uint16_t y, const uint16_t z,
                        const std::string& name);


    void save(const char* rel_path);
    void save(const std::string& rel_path);
};

#endif
