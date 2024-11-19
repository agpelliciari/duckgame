
#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include "common/dtosplayer.h"
#include "armor.h"
#include "match_map.h"
#include "physical_player.h"
#include "tuple.h"
#include "shooting_direction.h"
#include "weapon.h"
#include "cowboy_pistol_weapon.h"
#include "magnum_weapon.h"
#include "pewpew_laser_weapon.h"
#include "physical_bullet.h"
#include "spawn_place.h"
#include "duel_pistol.h"
#include "dropped_item.h"


class Player {

private:
    int id;                      // cppcheck-suppress unusedStructMember
    PhysicalPlayer object;       // cppcheck-suppress unusedStructMember
    bool is_alive;               // cppcheck-suppress unusedStructMember
    bool helmet;                // cppcheck-suppress unusedStructMember
    bool chest_armor;           // cppcheck-suppress unusedStructMember
    TypeMoveAction move_action;  // cppcheck-suppress unusedStructMember
    TypeDoingAction doing_action; // cppcheck-suppress unusedStructMember
    bool aim_up;                 // cppcheck-suppress unusedStructMember
    int life_points;              // cppcheck-suppress unusedStructMember
    ShootingDirection shooting_direction;  // cppcheck-suppress unusedStructMember
    std::unique_ptr<Weapon> weapon;               // cppcheck-suppress unusedStructMember

public:
    Player(int id, int initial_x, int initial_y);
    int get_id();
    bool is_still_alive();
    bool same_id(unsigned int id);

    void get_data(int& id, int& x, int& y, TypeWeapon& weapon, bool& helmet_equipped,
                  bool& chest_armor_equipped, TypeMoveAction& move_action, TypeDoingAction& doing_action);

    void still();
    void add_speed(int speed_x, int speed_y);
    void update(const MatchMap& colition_map);
    void stop_moving_x();
    void shoot(std::vector <PhysicalBullet> &bullets);
    void pick_up_item(std::vector<SpawnPlace> &spawn_places, std::vector<DroppedItem> &dropped_items);
    void drop_item(std::vector<DroppedItem> &dropped_items);
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
