

#include "action_command.h"

ActionCommand::ActionCommand(PlayerActionDTO action_, MatchLogic *match_logic_):
action(action_), match_logic(match_logic_) {
    this->command_map[0] = [this](){match_logic->still_player(action.playerind);};
    this->command_map[1] = [this](){match_logic->move_player_left(action.playerind);};
    this->command_map[2] = [this](){match_logic->move_player_right(action.playerind);};
    this->command_map[3] = [this](){match_logic->move_player_jump(action.playerind);};
    this->command_map[4] = [this](){match_logic->move_player_stay_down(action.playerind);};
}

void ActionCommand::execute(){
    this -> command_map[action.type]();
}
