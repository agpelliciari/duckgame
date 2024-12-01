

#ifndef BOX_H
#define BOX_H

#include <vector>
#include "tuple.h"
#include "common/dtosplayer.h"
#include "common/dtosmap.h"
#include "common/dtosgame.h"
#include "common/dtosobject.h"
#include "weapon.h"
#include <memory>
#include <cstdlib>
#include <ctime>
#include "cowboy_pistol_weapon.h"
#include "magnum_weapon.h"
#include "pewpew_laser_weapon.h"
#include "duel_pistol.h"
#include "sniper_weapon.h"
#include "shotgun_weapon.h"
#include "ak47_weapon.h"
#include "laser_rifle_weapon.h"
#include "grenade_weapon.h"

class Box {

    private:
        int id;
        Tuple spawn_point;
        Tuple dimension;
        bool spawned;
        int life_points;
        std::vector<TypeDynamicObject> possible_rewards;


    public:

        Box(int id, int spawn_x, int spawn_y);
        Tuple get_spawn_point();
        Tuple get_dimension();
        bool is_spawned();
        bool destroyed();
        void take_damage();
        bool same_id(int id);
        std::unique_ptr<Weapon> get_item();
        
        int get_id() const;


};


#endif  // BOX_H
