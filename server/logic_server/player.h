#include "common/dtosplayer.h"

#include "action.h"
#include "armor.h"
#include "weapon.h"
#include "physical_object.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {

    private:
        unsigned int id;          // cppcheck-suppress unusedStructMember
        PhysicalObject object;    // cppcheck-suppress unusedStructMember
        bool is_alive;            // cppcheck-suppress unusedStructMember
        Weapon weapon;            // cppcheck-suppress unusedStructMember
        Armor helmet;             // cppcheck-suppress unusedStructMember
        Armor chest_armor;        // cppcheck-suppress unusedStructMember
        Action move_action;       // cppcheck-suppress unusedStructMember

    public:
        Player(unsigned int id, int initial_x, int initial_y);

        bool same_id(unsigned int id);

        void get_data(int& id, int& x, int& y, const TypeWeapon& weapon, const bool& helmet_equipped,
                  const bool& chest_armor_equipped, TypeMoveAction& move_action);

        void still();
        void add_speed(int speed_x, int speed_y);
        void update_position();
};


#endif  // PLAYER_H
