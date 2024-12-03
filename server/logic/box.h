

#ifndef BOX_H
#define BOX_H

#include <vector>
#include "server/logic/physical/tuple.h"
#include "common/dtosplayer.h"
#include "common/dtosmap.h"
#include "common/dtosgame.h"
#include "common/dtosobject.h"
#include "server/logic/weapons/weapon.h"
#include <memory>
#include <cstdlib>
#include <ctime>
#include "server/logic/weapons/cowboy_pistol_weapon.h"
#include "server/logic/weapons/magnum_weapon.h"
#include "server/logic/weapons/pewpew_laser_weapon.h"
#include "server/logic/weapons/duel_pistol.h"
#include "server/logic/weapons/sniper_weapon.h"
#include "server/logic/weapons/shotgun_weapon.h"
#include "server/logic/weapons/ak47_weapon.h"
#include "server/logic/weapons/laser_rifle_weapon.h"
#include "server/logic/weapons/grenade_weapon.h"

class Box {

    private:
        int id;
        Tuple spawn_point;
        Tuple dimension;
        bool spawned;
        int life_points;
        std::vector<TypeDynamicObject> possible_rewards;


    public:

        Box(int id, int hp, int spawn_x, int spawn_y);
        Tuple get_spawn_point();
        Tuple get_dimension();
        bool is_spawned();
        bool destroyed();
        void take_damage();
        bool same_id(int id);
        std::unique_ptr<Weapon> get_item(const int base_mun);
        
        int get_id() const;


};


#endif  // BOX_H
