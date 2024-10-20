#include "player.h"
#include "./match_logic.h"
#include "./match_queue.h"
#include "./box.h"
#include <list>
#include "server/playercontainer.h"

#ifndef MATCH_STATE_H
#define MATCH_STATE_H

class MatchState {

    private:
        MatchLogic match_logic;
    public:
        MatchState();

        void add_player(Player player);

        void loop(PlayerContainer& observer, MatchQueue& acciones);

        ~MatchState();
};

#endif //MATCH_STATE_H
