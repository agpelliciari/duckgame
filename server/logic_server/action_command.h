#include "command.h"
#include "match_logic.h"
#include "common/dtosplayer.h"
#include <functional>
#include <map>


#ifndef ACTION_COMMAND_H
#define ACTION_COMMAND_H



class ActionCommand : public Command {

    private:
        PlayerActionDTO action;
        MatchLogic *match_logic;
        std::map<int, std::function<void()>> command_map;

    public:
        ActionCommand(PlayerActionDTO action, MatchLogic *match_logic);

        void execute() override;
        virtual ~ActionCommand() {}
};



#endif //ACTION_COMMAND_H
