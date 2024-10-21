#include "player.h"
#include "action_command.h"
#include "./match_logic.h"
#include "./match_queue.h"
#include "common/dtosplayer.h"
#include "common/dtos.h"
#include "./box.h"
#include <list>
#include <vector>
#include "server/playercontainer.h"

#ifndef MATCH_STATE_H
#define MATCH_STATE_H

class MatchState {

    private:
        bool running;
        MatchLogic match_logic;
        std::vector <ActionCommand> commands;
        MatchQueue acciones;

    public:
        MatchState();
        void pushAction(const PlayerActionDTO& action);
        //void add_player(Player player);
        void receive_commands(MatchQueue& acciones);
        void execute_commands();
        void send_results();
        void loop(PlayerContainer& observer);
        ~MatchState();

};

#endif //MATCH_STATE_H
