#include "common/dtosobject.h"
#include "server/logic/physical/tuple.h"
#include "server/logic/weapons/weapon.h"
#include <vector>
#include <memory>
#include "server/logic/weapons/cowboy_pistol_weapon.h"
#include "server/logic/weapons/magnum_weapon.h"
#include "server/logic/weapons/pewpew_laser_weapon.h"
#include "server/logic/weapons/duel_pistol.h"
#include "server/logic/weapons/sniper_weapon.h"
#include "server/logic/weapons/shotgun_weapon.h"
#include "server/logic/weapons/ak47_weapon.h"
#include "server/logic/weapons/laser_rifle_weapon.h"
#include "server/logic/weapons/grenade_weapon.h"
#include "server/logic/weapons/banana_weapon.h"

#ifndef SPAWN_PLACE_H
#define SPAWN_PLACE_H

enum SpawnActionType{
    NO_ACTION,
    PICKUP_WEAPON,
    PICKUP_HELMET,
    PICKUP_ARMOR
};

class SpawnPlace {

    private:
        std::unique_ptr<Weapon> possible_weapon;
        bool possible_helmet;
        bool possible_armor;
        TypeDynamicObject item;
        Tuple spawn_point;
        Tuple dimension;
        bool spawned;
        int time_respawn;
        float time_sleep;
        int timer;
        int seed;

    public:
        SpawnPlace (int position_x, int position_y, int range_x, int range_y,
                   int time_respawn, float time_sleep, int seed);


        Tuple get_spawn_point();
        Tuple get_dimension();
        bool is_on_range(int player_position_x, int player_position_y);
        bool is_spawned();
        void spawn_item(int base_mun);
        void pass_time(int base_mun);
        
        void take_item(TypeDynamicObject &item);
        
        SpawnActionType get_action();
        void get_item(std::unique_ptr<Weapon>& weapon);
        
        void get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_);
        TypeDynamicObject get_item();
};



#endif //SPAWN_PLACE_H
