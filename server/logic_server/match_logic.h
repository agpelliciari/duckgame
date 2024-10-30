#include <list>
#include <vector>
#include <map>
#include <functional>


#include "common/dtosplayer.h"

#include "player.h"

#ifndef MATCH_LOGIC_H
#define MATCH_LOGIC_H


class MatchLogic {

private:
    std::list<Player> players;  // cppcheck-suppress unusedStructMember
	std::map<int, std::function<void(int)>> command_map;  // cppcheck-suppress unusedStructMember

public:
    MatchLogic();

   	void execute_move_command(int action_type, int index);
    void add_player(int id);
    void still_player(int id_player);
    void move_player_left(int id_player);
    void move_player_right(int id_player);
    void move_player_jump(int id_player);
    void move_player_stay_down(int id_player);
    void get_dtos(std::vector<PlayerDTO>& dtos);
    void update_player_positions();
    ~MatchLogic();
};


#endif  // MATCH_LOGIC_H
