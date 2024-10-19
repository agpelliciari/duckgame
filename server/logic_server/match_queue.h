
#ifndef MATCH_QUEUE_H
#define MATCH_QUEUE_H

#include "common/dtosplayer.h"

class MatchQueue {
public:
    void notify(const PlayerActionDTO& action);
    void close();
};



#endif //MATCH_QUEUE_H
