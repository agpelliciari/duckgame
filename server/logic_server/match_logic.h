#include <functional>
#include <list>
#include <map>
#include <vector>

#include "common/dtosplayer.h"
#include "common/dtosmap.h"
#include "common/dtosgame.h"
#include "common/dtosobject.h"
#include "item.h"
#include "box.h"
#include "match_map.h"
#include "player.h"
#include "tuple.h"
#include "physical_bullet.h"

#ifndef MATCH_LOGIC_H
#define MATCH_LOGIC_H


class MatchLogic {

private:
    MatchMap colition_map;  // cppcheck-suppress unusedStructMember

    std::vector<Player> players;  // cppcheck-suppress unusedStructMember
    std::vector<Box> boxes;       // cppcheck-suppress unusedStructMember
    std::vector<Item> items;     // cppcheck-suppress unusedStructMember
    std::vector<PhysicalBullet> bullets; // cppcheck-suppress unusedStructMember

    // std::vector<std::vector<bool>> colition_map; // cppcheck-suppress unusedStructMember


    std::map<int, std::function<void(int)>> command_map;  // cppcheck-suppress unusedStructMember


public:
    MatchLogic();
    void execute_move_command(int action_type, int index);
    void add_player(int id);
    void add_player_speed(int id, int x, int y);
    void still_player(int id);
    void get_dtos(std::vector<PlayerDTO>& dtos, std::vector<DynamicObjDTO>& objects);
    void update_players();
    void update_colition_map();
    //void add_colition(PhysicalObject &object);
    void add_boxes(const std::vector<struct MapPoint>& boxes);
    void add_items(const std::vector<struct MapPoint>& items);
    void add_bullet(PhysicalBullet bullet);
    void update_bullets();
    void player_shoot(int index);
    void player_aim_up_start(int index);
    void player_aim_up_end(int index);
    void damage_player(int id);
    ~MatchLogic();
};


#endif  // MATCH_LOGIC_H
