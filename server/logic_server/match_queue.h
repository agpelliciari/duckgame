
#ifndef MATCH_QUEUE_H
#define MATCH_QUEUE_H

#include <mutex>
#include "match_logic.h"
#include "action_command.h"
#include "common/dtosplayer.h"
#include "common/queue.h"

class MatchQueue {

    private:
        std::mutex mutex;
        Queue<class ActionCommand> queue;
        MatchLogic &match_logic;


    public:
        MatchQueue(MatchLogic &match_logic);
        void push_command(const PlayerActionDTO& action);
        bool pop_command(ActionCommand& action);
        void close();
};

#endif //MATCH_QUEUE_H
