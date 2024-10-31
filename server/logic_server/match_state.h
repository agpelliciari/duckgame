#include <atomic>
#include <list>
#include <vector>

#include "./box.h"
#include "./match_logic.h"
#include "./match_queue.h"
#include "./matchobserver.h"
#include "common/dtos.h"
#include "common/dtosplayer.h"

#include "action_command.h"
#include "player.h"

#ifndef MATCH_STATE_H
#define MATCH_STATE_H

class MatchState {

private:
    std::atomic<bool> running;            // cppcheck-suppress unusedStructMember
    MatchLogic match_logic;               // cppcheck-suppress unusedStructMember
    MatchQueue acciones;                  // cppcheck-suppress unusedStructMember
    std::vector<ActionCommand> commands;  // cppcheck-suppress unusedStructMember

public:
    MatchState();
    void pushAction(const PlayerActionDTO& action);
    // void add_player(Player player);
    void receive_commands();
    void execute_commands();

    void send_results(MatchObserver& observer);
    void start_players(MatchObserver& observer);
    void step();

    void loop(MatchObserver& observer);
    void stop();
    ~MatchState();
};

#endif  // MATCH_STATE_H
