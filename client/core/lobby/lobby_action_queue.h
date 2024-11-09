#ifndef LOBBY_ACTION_QUEUE
#define LOBBY_ACTION_QUEUE

#include "common/dtoslobby.h"
#include "common/queue.h"

class LobbyActionQueue {
    Queue<lobby_action> actions;

public:
    LobbyActionQueue();
    void doaction(const lobby_action& action);
    void notifyStart();
    void close();
    lobby_action popaction();

    ~LobbyActionQueue() {}
};

#endif
