#ifndef LOBBY_CLIENT_SENDER_H
#define LOBBY_CLIENT_SENDER_H

#include "common/dtoslobby.h"
#include "common/queue.h"

class LobbyClientSender {
    Queue<lobby_action> actions;

public:
    LobbyClientSender();
    void doaction(const lobby_action& action);
    void notifyStart();
    void close();
    lobby_action popaction();

    ~LobbyClientSender() {}
};

#endif
