#include <atomic>
#include <list>
#include <vector>

#include "./box.h"
#include "./match_logic.h"
#include "./match_queue.h"
#include "common/dtos.h"
#include "common/dtosplayer.h"
#include "server/playercontainer.h"

#include "action_command.h"
#include "player.h"

#ifndef MATCH_STATE_H
#define MATCH_STATE_H

class MatchState {

private:
    std::atomic<bool> running;  // cppcheck-suppress unusedStructMember
    MatchLogic match_logic;     // cppcheck-suppress unusedStructMember
    MatchQueue acciones;        // cppcheck-suppress unusedStructMember

public:
    MatchState();
    void pushAction(const PlayerActionDTO& action);
    // void add_player(Player player);
    void receive_commands(MatchQueue& acciones);
    void execute_commands();
    void send_results();
    void loop(PlayerContainer& observer);
    ~MatchState();
};

#endif  // MATCH_STATE_H
