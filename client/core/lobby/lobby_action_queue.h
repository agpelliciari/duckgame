#ifndef LOBBY_ACTION_QUEUE
#define LOBBY_ACTION_QUEUE

#include <string>

#include "common/dtoslobby.h"
#include "common/queue.h"

class LobbyActionQueue {
    Queue<lobby_action> actions;
    std::string mapname;  // cppcheck-suppress unusedStructMember

public:
    LobbyActionQueue();
    void doaction(const lobby_action& action);
    void notifyStart(const std::string& namemap);
    void close();
    lobby_action popaction();

    const std::string& getMapName() const;

    ~LobbyActionQueue() {}
};

#endif
