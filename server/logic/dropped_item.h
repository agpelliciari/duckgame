
#ifndef DROPPED_ITEM_H
#define DROPPED_ITEM_H

#include <vector>
#include <memory>
#include "server/logic/weapons/weapon.h"
#include "server/logic/physical/tuple.h"
#include "server/logic/weapons/cowboy_pistol_weapon.h"
#include "server/logic/weapons/magnum_weapon.h"
#include "server/logic/weapons/pewpew_laser_weapon.h"
#include "server/logic/weapons/duel_pistol.h"
#include "server/logic/weapons/sniper_weapon.h"
#include "server/logic/weapons/shotgun_weapon.h"
#include "server/logic/weapons/banana_weapon.h"


class DroppedItem {

    private:

        bool alive;
        Tuple position;
        Tuple dimension;
        std::unique_ptr<Weapon> weapon;

    public:
        DroppedItem(std::unique_ptr<Weapon> weapon, int position_x, int position_y, int dimension_x, int dimension_y);

        Tuple get_position();
        Tuple get_dimension();
        bool is_on_range(int player_position_x, int player_position_y);
        bool is_alive();
        std::unique_ptr<Weapon> get_weapon();
        void get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_);
};



#endif //DROPPED_ITEM_H
