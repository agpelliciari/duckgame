#include <vector>

#include "common/dtosplayer.h"

#include "armor.h"
#include "match_map.h"
#include "physical_player.h"
#include "tuple.h"
#include "weapon.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {

private:
    unsigned int id;             // cppcheck-suppress unusedStructMember
    PhysicalPlayer object;       // cppcheck-suppress unusedStructMember
    bool is_alive;               // cppcheck-suppress unusedStructMember
    Weapon weapon;               // cppcheck-suppress unusedStructMember
    Armor helmet;                // cppcheck-suppress unusedStructMember
    Armor chest_armor;           // cppcheck-suppress unusedStructMember
    TypeMoveAction move_action;  // cppcheck-suppress unusedStructMember

public:
    Player(unsigned int id, int initial_x, int initial_y);

    bool same_id(unsigned int id);

    void get_data(int& id, int& x, int& y, const TypeWeapon& weapon, const bool& helmet_equipped,
                  const bool& chest_armor_equipped, TypeMoveAction& move_action);

    void still();
    void add_speed(int speed_x, int speed_y);
    void update(const MatchMap& colition_map);
    void stop_moving_x();
    //Tuple get_position();
    Tuple get_map_position();
    Tuple get_dimension();
};


#endif  // PLAYER_H
