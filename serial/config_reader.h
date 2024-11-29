#ifndef LIB_ConfigReader_H
#define LIB_ConfigReader_H

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

#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

#include "common/dtosobject.h"

typedef ryml::NodeRef config_item_t;

class ConfigReader {
public:
    static const char* DMG_BASE;          // cppcheck-suppress unusedStructMember
    static const char* MUNITION_BASE;          // cppcheck-suppress unusedStructMember
    
    static const char* BASE_GRAVITY;          // cppcheck-suppress unusedStructMember
    
    static const char* EXPLOSION_RADIUS;  // cppcheck-suppress unusedStructMember
    static const char* FPS;               // cppcheck-suppress unusedStructMember
    static const char* ROUNDS_PER_SET;    // cppcheck-suppress unusedStructMember
    static const char* WINS_NEEDED;      // cppcheck-suppress unusedStructMember
    
    static const char* PLAYER_SPEED;        // cppcheck-suppress unusedStructMember
    static const char* PLAYER_HEALTH;     // cppcheck-suppress unusedStructMember
    static const char* PLAYER_JMP_FORCE;     // cppcheck-suppress unusedStructMember
    static const char* PLAYER_FLAP_FORCE;     // cppcheck-suppress unusedStructMember
    static const char* PLAYER_FLAPS;     // cppcheck-suppress unusedStructMember
    
    static const char* MAGNUM_DMG;        // cppcheck-suppress unusedStructMember
    static const char* MAGNUM_MUNITION;   // cppcheck-suppress unusedStructMember
    
    static const char* ARMOR_HEALTH;      // cppcheck-suppress unusedStructMember
    static const char* HELMET_HEALTH;      // cppcheck-suppress unusedStructMember
    
    static const char* ITEM_SPAWN_TIME;      // cppcheck-suppress unusedStructMember
    static const char* BOX_HEALTH;      // cppcheck-suppress unusedStructMember
    
protected:
    //size_t root_id;
    ryml::Tree tree;  // cppcheck-suppress unusedStructMember
    
    ryml::NodeRef root;    
    
    bool checkInvalid(config_item_t& item);
    void readU16(config_item_t item,uint16_t& out);
    void readShort(config_item_t item,short& out);
public:
    explicit ConfigReader(const std::string& src);
    // Asumamos por ahora que no se quiere permitir copias..
    ConfigReader(const ConfigReader&) = delete;
    ConfigReader& operator=(const ConfigReader&) = delete;

    // Permitamos el mov... por mas que no sea realmente eficiente.
    ConfigReader(ConfigReader&&) = delete;
    ConfigReader& operator=(ConfigReader&&) = delete;

    // Loadings de datos en si.
    void readBaseDmgMunition(uint16_t& dmg_base,uint16_t& munition_info);
    void readMagnumInfo(uint16_t& dmg_magnum,uint16_t& munition_magnum);
    
    void readPlayerInfo(uint16_t& health,uint16_t& speed,short& jmp_force,short& flap_force,uint16_t& flaps);
    void readDefenseInfo(uint16_t& armor_health,uint16_t& helmet_health);
    
    void readGravity(short& out);
    void readExpRadius(uint16_t& out);
    void readMSDelay(uint16_t& delay);
    void readRoundsPerSet(uint16_t& out);
    void readWinsNeeded(uint16_t& out);    
    void readItemSpawnTime(uint16_t& out);    
    void readBoxHealth(uint16_t& out);    
    
};
#endif
