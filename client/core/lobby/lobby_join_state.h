#ifndef LOBBY_JOIN_SENDER_H
#define LOBBY_JOIN_SENDER_H


#include "./lobby_state_recv.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyJoinState: public LobbyStateRecv {
protected:
    void run() override;

public:
    // Los default sin pasar por socket/protocol.
    explicit LobbyJoinState(Messenger& _messenger, GameContext& _context, LobbyListener& _listener);

    LobbyJoinState(LobbyJoinState&&) = delete;
    LobbyJoinState& operator=(LobbyJoinState&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyJoinState(const LobbyJoinState&) = delete;
    LobbyJoinState& operator=(const LobbyJoinState&) = delete;

    // void doaction(const lobby_action& action);
    void joinLobby();
    bool isrunning();

    // Lobby state
    // bool endstate() override;

    //~LobbyJoinState();
};

#endif
