#include <list>
#include <vector>
#include <map>
#include <functional>

#include "tuple.h"
#include "common/dtosplayer.h"
#include "box.h"
#include "player.h"

#ifndef MATCH_LOGIC_H
#define MATCH_LOGIC_H


class MatchLogic {

private:
    std::vector<Player> players;  // cppcheck-suppress unusedStructMember
    std::vector<Box> boxes; // cppcheck-suppress unusedStructMember
    std::map<Tuple, bool> game_map; // cppcheck-suppress unusedStructMember
	std::map<int, std::function<void(int)>> command_map;  // cppcheck-suppress unusedStructMember


public:
    MatchLogic();

   	void execute_move_command(int action_type, int index);
    void add_player(int id);
    void get_dtos(std::vector<PlayerDTO>& dtos);
    void update_player_positions();
    ~MatchLogic();
};


#endif  // MATCH_LOGIC_H
