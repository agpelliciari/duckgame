#include "common/dtosobject.h"
#include "tuple.h"
#include "weapon.h"
#include <vector>
#include <memory>
#include "cowboy_pistol_weapon.h"

#ifndef SPAWN_PLACE_H
#define SPAWN_PLACE_H

class SpawnPlace {

    private:
        // TODO pasar luego a un vector de unique_ptr
        std::vector<std::unique_ptr<Weapon>> possible_weapons;
        TypeDynamicObject item;
        Tuple spawn_point;
        Tuple dimension;
        bool spawned;
        int time_respawn;
        float time_sleep;
        int timer;

    public:
        SpawnPlace (TypeDynamicObject item, int position_x, int position_y,
             int range_x, int range_y, int time_respawn, float time_sleep);


        Tuple get_spawn_point();
        Tuple get_dimension();
        bool is_on_range(int player_position_x, int player_position_y);
        bool is_spawned();
        void spawn_item();
        void pass_time();
        void take_item(TypeDynamicObject &item);
         std::unique_ptr<Weapon> get_weapon();
        void get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_);
};



#endif //SPAWN_PLACE_H
