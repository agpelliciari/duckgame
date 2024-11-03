#ifndef LOBBY_ACTION_LISTENER
#define LOBBY_ACTION_LISTENER

#include <string>

#include "./lobby_client_sender.h"
#include "common/clientprotocol.h"
#include "common/dtos.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyActionListener: private Thread {
protected:
    ClientProtocol& protocol;
    LobbyClientSender& actions;
    void run() override;

public:
    // Los default sin pasar por socket/protocol.
    explicit LobbyActionListener(ClientProtocol& _protocol, LobbyClientSender& _actions);

    LobbyActionListener(LobbyActionListener&&);
    LobbyActionListener& operator=(LobbyActionListener&&);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyActionListener(const LobbyActionListener&) = delete;
    LobbyActionListener& operator=(const LobbyActionListener&) = delete;

    void begin();

    void notifyCancel();
    void doaction(const lobby_action& action);
    void notifyStart();

    bool isrunning();

    ~LobbyActionListener();
};

#endif
