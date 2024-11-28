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
    player_jmp_force(40),
    player_flap_force(10),
    player_flaps(9),
    frame_delay(MS_FPS),
    rounds_per_set(5),
    wins_needed(10),
    magnum_dmg(1),
    magnum_munition(1),
    armor_health(1),
    box_health(1),
    item_spawn_time(1)
    {}


Configuration::Configuration(const char* config): Configuration() {
        std::cout << "Loading configs from " << config<<std::endl;
        try{    
            ConfigReader reader(config);
            
            reader.readBaseDmgMunition(base_dmg, base_munition);
            // Dejenme usar printf!!!!
            printf("Base dmg: %u base munition: %u\n",base_dmg, base_munition);
            
            reader.readMagnumInfo(magnum_dmg, magnum_munition);
            printf("magnum dmg: %u magnum munition: %u\n",magnum_dmg, magnum_munition);

            reader.readPlayerInfo(player_health, player_speed,player_jmp_force,player_flap_force,player_flaps);
            printf("player hp: %u speed: %u jmp force: %u\n",player_health, player_speed,player_jmp_force);
            printf("player flap_force: %u flap_count: %u\n",player_flap_force,player_flaps);
            
            
            
            reader.readDefenseInfo(armor_health, helmet_health);
            printf("armor hp: %u helmet_hp: %u\n",armor_health, helmet_health);
            
            reader.readExpRadius(explosion_radius);
            printf("exp radius: %u\n",explosion_radius);
            
            reader.readBoxHealth(box_health);
            printf("box health: %u\n",box_health);

            reader.readItemSpawnTime(item_spawn_time);
            printf("item spawn time: %u\n",item_spawn_time);

            reader.readMSDelay(frame_delay);
            printf("delay frame: %ums\n",frame_delay);
            reader.readGravity(gravity);
            printf("gravity : %d\n",gravity);

            reader.readRoundsPerSet(rounds_per_set);
            printf("rounds per set : %u\n",rounds_per_set);
            
            reader.readWinsNeeded(wins_needed);
            printf("wins needed : %u\n",wins_needed);
            
        } catch(const SerialError& error){
            std::cerr << "Failed read of configurations! " << error.what() << std::endl;
        }        
    }

