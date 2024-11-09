#ifndef LOBBY_ACTION_SENDER
#define LOBBY_ACTION_SENDER

#include <string>

#include "./lobby_action_queue.h"
#include "common/clientprotocol.h"
#include "common/thread.h"


// Thread para consumir a la lobby action queue.
class LobbyActionSender: private Thread {
protected:
    ClientProtocol& protocol;
    LobbyActionQueue& actions;
    void run() override;

public:
    explicit LobbyActionSender(ClientProtocol& _protocol, LobbyActionQueue& _actions);

    LobbyActionSender(LobbyActionSender&&);
    LobbyActionSender& operator=(LobbyActionSender&&);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyActionSender(const LobbyActionSender&) = delete;
    LobbyActionSender& operator=(const LobbyActionSender&) = delete;

    void begin();

    void notifyCancel();
    void doaction(const lobby_action& action);
    void notifyStart();

    bool isrunning();

    ~LobbyActionSender();
};

#endif
