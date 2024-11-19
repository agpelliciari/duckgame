#include <functional>
#include <list>
#include <map>
#include <vector>

#include "common/dtosplayer.h"
#include "common/dtosmap.h"
#include "common/dtosgame.h"
#include "common/dtosobject.h"
#include "spawn_place.h"
#include "box.h"
#include "match_map.h"
#include "player.h"
#include "tuple.h"
#include "collision.h"
#include "type_collision.h"
#include "physical_bullet.h"
#include "dropped_item.h"

#ifndef MATCH_LOGIC_H
#define MATCH_LOGIC_H


class MatchLogic {

private:
    MatchMap colition_map;  // cppcheck-suppress unusedStructMember

    std::vector<Player> players;  // cppcheck-suppress unusedStructMember
    //std::vector<int> id_alive_players;    // cppcheck-suppress unusedStructMember
    std::vector<Box> boxes;       // cppcheck-suppress unusedStructMember
    std::vector<SpawnPlace> spawn_places;     // cppcheck-suppress unusedStructMember
    std::vector<PhysicalBullet> bullets; // cppcheck-suppress unusedStructMember
    std::vector<MapPoint> blocks;  // cppcheck-suppress unusedStructMember
    std::vector<MapPoint> spawn_points; // cppcheck-suppress unusedStructMember
    std::vector<DroppedItem> dropped_items; // cppcheck-suppress unusedStructMember

    // std::vector<std::vector<bool>> colition_map; // cppcheck-suppress unusedStructMember


    std::map<int, std::function<void(int)>> command_map;  // cppcheck-suppress unusedStructMember


public:
    MatchLogic();
    void execute_move_command(int action_type, int index);
    void add_player(int id, int spawn_point_index);
    void add_player_speed(int id, int x, int y);
    void still_player(int id);
    void get_dtos(std::vector<PlayerDTO>& dtos, std::vector<DynamicObjDTO>& objects);
    void update_players(std::vector<int> &id_alive_players);
    void update_colition_map();
    //void add_colition(PhysicalObject &object);
    void add_item_spawns(const std::vector<struct MapPoint>& items_spawns);
    void add_boxes(const std::vector<struct MapPoint>& boxes);
    void add_items(const std::vector<struct MapPoint>& items);
    void add_blocks(const std::vector<struct MapPoint>& blocks);
    void add_spawn_points(const std::vector<struct MapPoint>& spawn_points);
    void add_bullet(PhysicalBullet bullet);
    void update_bullets();
    void player_shoot(int index);
    void player_aim_up_start(int index);
    void player_aim_up_end(int index);
    void player_stay_down_start(int index);
    void player_stay_down_end(int index);
    void damage_player(int id);
    void damage_box(int id);
    void clear_players();
    void clear_objects();
    void player_pick_up_item(int id);
    void player_drop_item(int id);
    void update_dropped_items();
    ~MatchLogic();
};


#endif  // MATCH_LOGIC_H
