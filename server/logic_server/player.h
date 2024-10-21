#include "common/dtosplayer.h"

#include "action.h"
#include "armor.h"
#include "coordinates.h"
#include "weapon.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {

private:
    int id;                   // cppcheck-suppress unusedStructMember
    bool is_alive;            // cppcheck-suppress unusedStructMember
    Coordinates coordinates;  // cppcheck-suppress unusedStructMember
    Weapon weapon;            // cppcheck-suppress unusedStructMember
    Armor helmet;             // cppcheck-suppress unusedStructMember
    Armor chest_armor;        // cppcheck-suppress unusedStructMember
    Action move_action;       // cppcheck-suppress unusedStructMember

public:
    Player(int id, int initial_x, int initial_y);

    bool same_id(int id);

    void get_data(const int& id, const int& x, const int& y, const TypeWeapon& weapon,
                  const bool& helmet_equipped, const bool& chest_armor_equipped,
                  const TypeMoveAction& move_action);

    void still();
    void move_right();
    void move_left();
    void stay_down();
    void jump();
};


#endif  // PLAYER_H
