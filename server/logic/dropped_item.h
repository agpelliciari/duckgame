
#ifndef DROPPED_ITEM_H
#define DROPPED_ITEM_H

#include <vector>
#include <memory>
#include "weapon.h"
#include "tuple.h"
#include "cowboy_pistol_weapon.h"
#include "magnum_weapon.h"
#include "pewpew_laser_weapon.h"
#include "duel_pistol.h"
#include "sniper_weapon.h"
#include "shotgun_weapon.h"

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
