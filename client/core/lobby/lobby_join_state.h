#ifndef LOBBY_JOIN_STATE_H
#define LOBBY_JOIN_STATE_H


#include "./lobby_state_recv.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"

// GameState para unirse a una lobby existente,
// que comparte la parte de recibir info de la lobby del server.
class LobbyJoinState: public LobbyStateRecv {
protected:
    void run() override;
    bool tryJoinLobbyFail();

public:
    explicit LobbyJoinState(Messenger& _messenger, GameContext& _context, LobbyListener& _listener);

    LobbyJoinState(LobbyJoinState&&) = delete;
    LobbyJoinState& operator=(LobbyJoinState&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyJoinState(const LobbyJoinState&) = delete;
    LobbyJoinState& operator=(const LobbyJoinState&) = delete;

    // Inicia el thread y verifica lo necesario para joinear a una lobby
    void joinLobby();

    bool isrunning();
    
    ~LobbyJoinState();
};

#endif
