#include "./config_reader.h"

#include <fstream>
#include <iostream>
//#include <errno.h>


#include "common/serialerror.h"
#include "common/core/liberror.h"


ConfigReader::ConfigReader(const std::string& src){

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
    } else {
        throw SerialError("Failed to read the file to deserialize ");
        //throw LibError(errno, "Failed to read the file to deserialize ");
    }
}

bool ConfigReader::checkInvalid(config_item_t& item){
     return item.invalid() || item.is_seed();     
}
void ConfigReader::readU16(config_item_t item, uint16_t& out){
    if(checkInvalid(item)){
        return;
    }
    
    item >> out;
}


void ConfigReader::readShort(config_item_t item, short& out){
    if(checkInvalid(item)){
        return;
    }
    item >> out;
}






const char* ConfigReader::DMG_BASE = "base_dmg";          
const char* ConfigReader::MUNITION_BASE = "base_munition";          
const char* ConfigReader::BASE_GRAVITY = "gravity";          

const char* ConfigReader::EXPLOSION_RADIUS = "explosion_radius";  
const char* ConfigReader::PLAYER_SPEED = "duck_speed";        
const char* ConfigReader::PLAYER_HEALTH = "duck_health";     
const char* ConfigReader::PLAYER_JMP_FORCE = "duck_jump_force";     
const char* ConfigReader::PLAYER_FLAP_FORCE = "duck_flap_force";     
const char* ConfigReader::PLAYER_FLAPS = "duck_max_flaps";     
const char* ConfigReader::PLAYER_FLAP_GRAVITY = "duck_flap_gravity";     



const char* ConfigReader::FPS = "fps";               
const char* ConfigReader::ROUNDS_PER_SET = "rounds_per_set";    
const char* ConfigReader::WINS_NEEDED = "wins_needed";      

const char* ConfigReader::ARMOR_HEALTH = "armor_health";       
const char* ConfigReader::HELMET_HEALTH= "helmet_health";      

const char* ConfigReader::ITEM_SPAWN_TIME= "item_respawn_time_sec";      
const char* ConfigReader::BOX_HEALTH= "box_health";  



void ConfigReader::readGravity(short& out){ readShort(root[ConfigReader::BASE_GRAVITY], out); }
void ConfigReader::readExpRadius(uint16_t& out){ readU16(root[ConfigReader::EXPLOSION_RADIUS], out); }
void ConfigReader::readRoundsPerSet(uint16_t& out){ readU16(root[ConfigReader::ROUNDS_PER_SET], out);}
void ConfigReader::readWinsNeeded(uint16_t& out){ readU16(root[ConfigReader::WINS_NEEDED], out); }

void ConfigReader::readItemSpawnTime(uint16_t& out){ readU16(root[ConfigReader::ITEM_SPAWN_TIME], out); }
void ConfigReader::readBoxHealth(uint16_t& out){ readU16(root[ConfigReader::BOX_HEALTH], out); }

void ConfigReader::readBaseDmgMunition(uint16_t& dmg_base,uint16_t& base_munition){
    readU16(root[ConfigReader::DMG_BASE], dmg_base);
    readU16(root[ConfigReader::MUNITION_BASE], base_munition);
}

void ConfigReader::readPlayerInfo(uint16_t& health,short& speed,short& jmp_force,
                                  short& flap_force,uint16_t& flaps,short& flap_grav){
    readShort(root[ConfigReader::PLAYER_SPEED], speed);
    readShort(root[ConfigReader::PLAYER_JMP_FORCE], jmp_force);
    readShort(root[ConfigReader::PLAYER_FLAP_FORCE], flap_force);
    readShort(root[ConfigReader::PLAYER_FLAP_GRAVITY], flap_grav);
    
    readU16(root[ConfigReader::PLAYER_HEALTH], health);
    readU16(root[ConfigReader::PLAYER_FLAPS], flaps);
    
    
}

void ConfigReader::readDefenseInfo(uint16_t& armor_health,uint16_t& helmet_health){
    readU16(root[ConfigReader::ARMOR_HEALTH], armor_health);
    readU16(root[ConfigReader::HELMET_HEALTH], helmet_health);
}

void ConfigReader::readMSDelay(int& fps, uint16_t& delay){
    config_item_t vl = root[ConfigReader::FPS];
    if(checkInvalid(vl)){
        return;
    }
    
    vl >> fps;
    if(fps <= 0){
        fps = 60;
    }
    
    
    delay = 1000/fps;
    
}

