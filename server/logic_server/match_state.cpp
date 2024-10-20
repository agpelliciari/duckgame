

#include "./match_state.h"

MatchState::MatchState():match_logic(){}

void MatchState::loop(PlayerContainer& observer, MatchQueue& acciones) {
     PlayerActionDTO act = {PlayerActionType::PICK_UP, 0 ,0}; 
     acciones.notify(act);
     observer.updateState(MatchDto(MatchStateType::INICIADA, 2));
}

void MatchState::add_player(Player player) {
    match_logic.add_player(player);
}

MatchState::~MatchState(){

}
