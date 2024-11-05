#ifndef LIB_SERIALIZER_H
#define LIB_SERIALIZER_H

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

#include "common/dtosobject.h"


class Serializer {
public:
    static const char* SIZE_X;         // cppcheck-suppress unusedStructMember
    static const char* SIZE_Y;         // cppcheck-suppress unusedStructMember
    static const char* BACKGROUND;     // cppcheck-suppress unusedStructMember
    static const char* TEXTURES;       // cppcheck-suppress unusedStructMember
    static const char* BOXES;          // cppcheck-suppress unusedStructMember
    static const char* ITEM_SPAWNS;    // cppcheck-suppress unusedStructMember
    static const char* PLAYER_SPAWNS;  // cppcheck-suppress unusedStructMember


    static const int POINT_X;  // cppcheck-suppress unusedStructMember
    static const int POINT_Y;  // cppcheck-suppress unusedStructMember

    static const int BLOCK_TEX;  // cppcheck-suppress unusedStructMember

protected:
    ryml::Tree tree;
    ryml::NodeRef root;
    ryml::NodeRef blocks;
    ryml::NodeRef boxes;
    ryml::NodeRef item_spawns;
    ryml::NodeRef player_spawns;

public:
    explicit Serializer(const uint16_t width, const uint16_t height);
    // Asumamos por ahora que no se quiere permitir copias..
    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    Serializer(Serializer&&) = delete;
    Serializer& operator=(Serializer&&) = delete;


    void setBackground(const char* rel_path);
    void setBackground(const std::string& rel_path);

    void addTexture(const uint16_t x, const uint16_t y, BlockTexture type);
    void addBox(const uint16_t x, const uint16_t y);
    void addItemSpawn(const uint16_t x, const uint16_t y);
    void addPlayerSpawn(const uint16_t x, const uint16_t y);


    void save(const char* rel_path);
    void save(const std::string& rel_path);
};
#endif
