#include <functional>
#include <list>
#include <map>
#include <vector>

#include "common/dtosplayer.h"
#include "common/dtosmap.h"
#include "common/dtosgame.h"
#include "common/dtosobject.h"
#include "box.h"
#include "match_map.h"
#include "player.h"
#include "tuple.h"

#ifndef MATCH_LOGIC_H
#define MATCH_LOGIC_H


class MatchLogic {

private:
    MatchMap colition_map;  // cppcheck-suppress unusedStructMember

    std::vector<Player> players;  // cppcheck-suppress unusedStructMember
    std::vector<Box> boxes;       // cppcheck-suppress unusedStructMember


    // std::vector<std::vector<bool>> colition_map; // cppcheck-suppress unusedStructMember


    std::map<int, std::function<void(int)>> command_map;  // cppcheck-suppress unusedStructMember


public:
    MatchLogic();
    void execute_move_command(int action_type, int index);
    void add_player(int id);
    void add_player_speed(int id, int x, int y);
    void get_dtos(std::vector<PlayerDTO>& dtos, std::vector<DynamicObjDTO>& objects);
    void update_players();
    void update_colition_map();
    //void add_colition(PhysicalObject &object);
    void add_boxes(const std::vector<struct MapPoint>& boxes);
    ~MatchLogic();
};


#endif  // MATCH_LOGIC_H
