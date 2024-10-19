

#include "match_state.h"

MatchState::MatchState(MatchQueue &match_queue_):match_logic(), match_queue(match_queue_){}

void MatchState::init() {

}

void MatchState::add_player(Player player) {
    match_logic.add_player(player);
}

