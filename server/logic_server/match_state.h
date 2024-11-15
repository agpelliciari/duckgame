#include <atomic>
#include <list>
#include <vector>

#include "./box.h"
#include "./match_logic.h"
#include "./match_queue.h"
#include "./matchobserver.h"
#include "common/dtosgame.h"
#include "common/dtosmap.h"
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
    MatchState(struct MapPoint size, std::vector<struct MapObject>& objects);
    void pushAction(const PlayerActionDTO& action);
    // void add_player(Player player);
    void receive_commands();
    void execute_commands();

    void send_results(MatchObserver& observer);
    void start_players(MatchObserver& observer);
    void add_objects(const struct ObjectsInfo& objects_info);
    void step();

    void playRound(MatchObserver& observer, MatchStatsInfo& stats);
    void stop();
    ~MatchState();
};

#endif  // MATCH_STATE_H
