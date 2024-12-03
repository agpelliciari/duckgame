#include <atomic>
#include <list>
#include <vector>

#include "server/logic/match_logic.h"
#include "server/logic/match_queue.h"
#include "common/dtosgame.h"
#include "common/dtosmap.h"
#include "common/dtosplayer.h"

#include "server/logic/action_command.h"

#include "server/core/matchobserver.h"
#include "server/core/configuration.h"

#ifndef MATCH_STATE_H
#define MATCH_STATE_H

class MatchState {

private:
    std::atomic<bool> running;            // cppcheck-suppress unusedStructMember
    MatchLogic match_logic;               // cppcheck-suppress unusedStructMember
    MatchQueue acciones;                  // cppcheck-suppress unusedStructMember
    std::vector<ActionCommand> commands;  // cppcheck-suppress unusedStructMember
    std::vector<int> id_alive_players;    // cppcheck-suppress unusedStructMember
    int max_rounds; // cppcheck-suppress unusedStructMember
    
    const Configuration& configs;
    MatchDto state_curr;

public:
    MatchState(const Configuration& _configs);
    void pushAction(const PlayerActionDTO& action);
    void receive_commands();
    void execute_commands();

    void send_results(MatchObserver& observer);
    void start_players(MatchObserver& observer, MatchStatsInfo& stats);
    void add_objects(const struct ObjectsInfo& objects_info);
    
    void reset_map(const struct ObjectsInfo& objects_info);
    
    void reset_objects(const struct ObjectsInfo& objects_info);
    void reset_players(MatchObserver& observer);
    
    void step();
    bool only_one_winner(MatchStatsInfo& stats, int &id_champion);
    void playRound(MatchObserver& observer, MatchStatsInfo& stats);
    void calculate_game_results(MatchStatsInfo& stats, int actual_winner);
    void stop();
    ~MatchState();
};

#endif  // MATCH_STATE_H
