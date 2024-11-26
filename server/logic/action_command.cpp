
#include <iostream>
#include "action_command.h"

ActionCommand::ActionCommand(PlayerActionDTO action_, MatchLogic* match_logic_):
        action(action_), match_logic(match_logic_) {}

void ActionCommand::execute() {
    if (action.type == PlayerActionType::NONE){
        std::cout<< "NONE" <<std::endl;
    }
    if (action.type == PlayerActionType::JUMP){
        std::cout<< "JUMP" <<std::endl;
    }
    if (action.type == PlayerActionType::MOVE_LEFT){
        std::cout<< "MOVE_LEFT" <<std::endl;
    }
    if (action.type == PlayerActionType::MOVE_LEFT_END){
        std::cout<< "MOVE_LEFT_END" <<std::endl;
    }
    if (action.type == PlayerActionType::MOVE_RIGHT){
        std::cout<< "MOVE_RIGHT" <<std::endl;
    }
    if (action.type == PlayerActionType::MOVE_RIGHT_END){
        std::cout<< "MOVE_RIGHT_END" <<std::endl;
    }

    match_logic->execute_move_command(action.type, action.playerind);
}
