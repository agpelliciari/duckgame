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
#include "server/core/configuration.h"
#include "bullet.h"
#include "grenade.h"

#ifndef MATCH_LOGIC_H
#define MATCH_LOGIC_H


class MatchLogic {

private:
    MatchMap colition_map;  // cppcheck-suppress unusedStructMember
    const Configuration& configs;
    
    std::vector<Player> players;  // cppcheck-suppress unusedStructMember
    //std::vector<int> id_alive_players;    // cppcheck-suppress unusedStructMember
    std::vector<Box> boxes;       // cppcheck-suppress unusedStructMember
    std::vector<SpawnPlace> spawn_places;     // cppcheck-suppress unusedStructMember
    std::vector<Bullet> bullets; // cppcheck-suppress unusedStructMember
    std::vector<MapPoint> blocks;  // cppcheck-suppress unusedStructMember
    std::vector<MapPoint> spawn_points; // cppcheck-suppress unusedStructMember
    std::vector<DroppedItem> dropped_items; // cppcheck-suppress unusedStructMember
    //std::vector<SoundEventType> sounds; // cppcheck-suppress unusedStructMember
    std::vector<Grenade> grenades;  // cppcheck-suppress unusedStructMember
    // std::vector<std::vector<bool>> colition_map; // cppcheck-suppress unusedStructMember


    std::map<int, std::function<void(int)>> command_map;  // cppcheck-suppress unusedStructMember


public:
    MatchLogic(const Configuration& _configs);
    void execute_move_command(int action_type, int index);
    void add_player(int id, int spawn_point_index);
    void add_player_speed(int id, int x, int y);
    void still_player(int id);
    void get_dtos(std::vector<PlayerDTO>& dtos, std::vector<DynamicObjDTO>& objects, std::vector<SoundEventType>& sounds);
    //void add_colition(PhysicalObject &object);
    void add_item_spawns(const std::vector<struct MapPoint>& items_spawns);
    void add_boxes(const std::vector<struct MapPoint>& boxes);
    void add_items(const std::vector<struct MapPoint>& items);
    void add_blocks(const std::vector<struct MapPoint>& blocks);
    void add_spawn_points(const std::vector<struct MapPoint>& spawn_points);
    void add_bullet(Bullet bullet);
    void player_shoot(int index);
    void player_shoot_end(int index);
    void player_aim_up_start(int index);
    void player_aim_up_end(int index);
    void player_stay_down_start(int index);
    void player_stay_down_end(int index);
    void damage_player(int id);
    void clear_players();
    void clear_objects();
    void player_toggle_pick_up_drop_item(int id);
    void player_jump_start(int id);
    void player_jump_end(int id);
    void resize_map(const int width, const int height);
    void reset_map();

    void player_cheat_1();
    void player_cheat_2();
    void player_cheat_3();

    void damage_box(int id,std::vector<GameEvent>& events);

    void update_bullets(std::vector<GameEvent>& events);
    void update_grenades(std::vector<GameEvent>& events);
    
    void update_dropped_items();
    void update_spawn_places();
    void update_spawn_points();
    void update_players(std::vector<int> &id_alive_players);
    void update_colition_map();


    ~MatchLogic();
};


#endif  // MATCH_LOGIC_H
