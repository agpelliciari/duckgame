
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "common/dtosplayer.h"
#include "armor.h"
#include "match_map.h"
#include "physical_player.h"
#include "tuple.h"
#include "shooting_direction.h"
#include "weapon.h"
#include "cowboy_pistol_weapon.h"
#include "physical_bullet.h"


class Player {

private:
    int id;                      // cppcheck-suppress unusedStructMember
    PhysicalPlayer object;       // cppcheck-suppress unusedStructMember
    bool is_alive;               // cppcheck-suppress unusedStructMember
    Armor helmet;                // cppcheck-suppress unusedStructMember
    Armor chest_armor;           // cppcheck-suppress unusedStructMember
    TypeMoveAction move_action;  // cppcheck-suppress unusedStructMember
    bool aim_up;                 // cppcheck-suppress unusedStructMember
    int life_points;              // cppcheck-suppress unusedStructMember
    ShootingDirection shooting_direction;  // cppcheck-suppress unusedStructMember
    CowboyPistolWeapon weapon;               // cppcheck-suppress unusedStructMember

public:
    Player(int id, int initial_x, int initial_y);
    int get_id();
    bool same_id(unsigned int id);

    void get_data(int& id, int& x, int& y, TypeWeapon& weapon, const bool& helmet_equipped,
                  const bool& chest_armor_equipped, TypeMoveAction& move_action);

    void still();
    void add_speed(int speed_x, int speed_y);
    void update(const MatchMap& colition_map);
    void stop_moving_x();
    void shoot(std::vector <PhysicalBullet> &bullets);
    void take_damage();
    void aim_up_start();
    void aim_up_end();
    void stay_down_start();
    void stay_down_end();
    void update_shooting_direction();
    Tuple get_map_position();
    Tuple get_dimension();
};


#endif  // PLAYER_H
