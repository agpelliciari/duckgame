#ifndef LIB_CONFIGURATIONS_H
#define LIB_CONFIGURATIONS_H

#include <cstdint>

class Configuration {    
public:
    uint16_t base_dmg;
    uint16_t base_munition;
    short gravity;
    

    uint16_t player_speed;
    uint16_t player_health;
    short player_jmp_force;
    short player_flap_force;
    uint16_t player_flaps;


    uint16_t explosion_radius;
    uint16_t frame_delay;
    uint16_t rounds_per_set;
    uint16_t wins_needed;
    
    uint16_t magnum_dmg;
    uint16_t magnum_munition;
    
    uint16_t armor_health;
    uint16_t helmet_health;

    uint16_t box_health;
    uint16_t item_spawn_time;

    Configuration(const char* config);
    Configuration();


    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    Configuration(Configuration&&) = delete;
    Configuration& operator=(Configuration&&) = delete;
    
};
#endif
