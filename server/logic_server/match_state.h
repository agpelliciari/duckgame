#include "player.h"
#include "./match_logic.h"
#include "./match_queue.h"
#include "./box.h"
#include <list>

#ifndef MATCH_STATE_H
#define MATCH_STATE_H

class MatchState {

    private:
        MatchLogic match_logic;
        MatchQueue &match_queue;

    public:
        MatchState(MatchQueue &match_queue);

        void add_player(Player player);

        void init();

        ~MatchState();
};

#endif //MATCH_STATE_H
