

#include "action_command.h"

ActionCommand::ActionCommand(PlayerActionDTO action_, MatchLogic* match_logic_):
        action(action_), match_logic(match_logic_) {}

void ActionCommand::execute() { match_logic->execute_move_command(action.type, action.playerind); }
