#ifndef LOBBY_CLIENT_SENDER_H
#define LOBBY_CLIENT_SENDER_H

#include "common/dtos.h"

class LobbyClientSender {
public:
    virtual void doaction(const lobby_action& action) = 0;
    virtual void notifyStart() = 0;

    virtual bool isrunning() = 0;
    virtual ~LobbyClientSender() {}
};

#endif
