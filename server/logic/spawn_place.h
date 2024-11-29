#include "common/dtosobject.h"
#include "tuple.h"
#include "weapon.h"
#include <vector>
#include <memory>
#include "cowboy_pistol_weapon.h"
#include "magnum_weapon.h"
#include "pewpew_laser_weapon.h"
#include "duel_pistol.h"
#include "sniper_weapon.h"
#include "shotgun_weapon.h"
#include "ak47_weapon.h"
#include "laser_rifle_weapon.h"

#ifndef SPAWN_PLACE_H
#define SPAWN_PLACE_H

class SpawnPlace {

    private:
        std::unique_ptr<Weapon> possible_weapon;
        TypeDynamicObject item;
        Tuple spawn_point;
        Tuple dimension;
        bool spawned;
        int time_respawn;
        float time_sleep;
        int timer;

    public:
        SpawnPlace (int position_x, int position_y, int range_x, int range_y,
                   int time_respawn, float time_sleep);


        Tuple get_spawn_point();
        Tuple get_dimension();
        bool is_on_range(int player_position_x, int player_position_y);
        bool is_spawned();
        void spawn_item();
        void pass_time();
        void take_item(TypeDynamicObject &item);
        std::unique_ptr<Weapon> get_weapon();
        void get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_);
        TypeDynamicObject get_item();
};



#endif //SPAWN_PLACE_H
