#include "player.h"
#include "common/dtosplayer.h"
#include <vector>
#include <list>

#ifndef MATCH_LOGIC_H
#define MATCH_LOGIC_H



class MatchLogic {

    private:
        std::list<Player> players;

    public:
        MatchLogic();

        void add_player(Player player);

        void move_player_left(int id_player);
        void move_player_right(int id_player);
        void move_player_jump(int id_player);
        void move_player_stay_down(int id_player);

        void get_dtos(std::vector <PlayerDTO> &dtos);

        ~MatchLogic();


};



#endif //MATCH_LOGIC_H
