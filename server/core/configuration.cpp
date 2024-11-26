#include "./configuration.h"

#include "serial/config_reader.h"
#include "common/serialerror.h"
#include <iostream>

#define FPS 30
#define MS_FPS 1000 / FPS

// Defaults vls
Configuration::Configuration(): 
    base_dmg(1),
    base_munition(1),
    gravity(10),
    explosion_radius(1),
    player_speed(1),
    player_health(3),
    player_jmp_force(5),
    frame_delay(MS_FPS),
    rounds_per_set(5),
    wins_needed(10),
    magnum_dmg(1),
    magnum_munition(1),
    armor_health(1),
    helmet_health(1){}


Configuration::Configuration(const char* config): Configuration() {
        std::cout << "Loading configs from " << config<<std::endl;
        /*
        try{    
            ConfigReader reader(config);
            
            reader.readBaseDmgMunition(base_dmg, base_munition);
            reader.readMagnumInfo(magnum_dmg, magnum_munition);

            reader.readPlayerInfo(player_health, player_speed,player_jmp_force);
            reader.readDefenseInfo(armor_health, helmet_health);
            
            reader.readExpRadius(explosion_radius);
            reader.readMSDelay(frame_delay);
            reader.readGravity(gravity);

            reader.readRoundsPerSet(rounds_per_set);
            
            reader.readWinsNeeded(wins_needed);
            
        } catch(const SerialError& error){
            std::cerr << "Failed read of configurations! " << error.what() << std::endl;
        }
        */
        
    }

