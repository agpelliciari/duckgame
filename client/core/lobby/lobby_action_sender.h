#ifndef LOBBY_ACTION_LISTENER
#define LOBBY_ACTION_LISTENER

#include <string>

#include "./lobby_action_queue.h"
#include "common/clientprotocol.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyActionSender: private Thread {
protected:
    ClientProtocol& protocol;
    LobbyActionQueue& actions;
    void run() override;

public:
    // Los default sin pasar por socket/protocol.
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
