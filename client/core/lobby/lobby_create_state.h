#ifndef LOBBY_CREATE_SENDER_H
#define LOBBY_CREATE_SENDER_H

#include <string>

#include "./lobby_action_queue.h"
#include "./lobby_state_recv.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/queue.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyCreateState: public LobbyStateRecv {
protected:
    LobbyActionQueue sender;
    void run() override;

public:
    // Los default sin pasar por socket/protocol.
    explicit LobbyCreateState(Messenger& _messenger, GameContext& _context,
                              LobbyListener& _listener);

    LobbyCreateState(LobbyCreateState&&) = delete;
    LobbyCreateState& operator=(LobbyCreateState&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyCreateState(const LobbyCreateState&) = delete;
    LobbyCreateState& operator=(const LobbyCreateState&) = delete;

    LobbyActionQueue& getSender();

    void createLobby();
};

#endif
