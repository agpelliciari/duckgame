#include <functional>
#include <map>

#include "common/dtosplayer.h"

#include "command.h"
#include "match_logic.h"


#ifndef ACTION_COMMAND_H
#define ACTION_COMMAND_H


class ActionCommand: public Command {

private:
    PlayerActionDTO action;                            // cppcheck-suppress unusedStructMember
    MatchLogic* match_logic;                           // cppcheck-suppress unusedStructMember
    //std::map<int, std::function<void()>> command_map;  // cppcheck-suppress unusedStructMember

public:
    ActionCommand(PlayerActionDTO action, MatchLogic* match_logic);

    void execute() override;
    virtual ~ActionCommand() {}
};


#endif  // ACTION_COMMAND_H
