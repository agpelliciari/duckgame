#ifndef LOBBY_JOIN_SENDER_H
#define LOBBY_JOIN_SENDER_H


#include "./base_lobby_state.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyJoinSender: public BaseLobbyState {
protected:
    void run() override;

public:
    // Los default sin pasar por socket/protocol.
    explicit LobbyJoinSender(ClientProtocol& _protocol, GameContext& _context,
                             LobbyListener& _listener);

    LobbyJoinSender(LobbyJoinSender&&);
    LobbyJoinSender& operator=(LobbyJoinSender&&);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyJoinSender(const LobbyJoinSender&) = delete;
    LobbyJoinSender& operator=(const LobbyJoinSender&) = delete;

    // void doaction(const lobby_action& action);
    void joinLobby();
    bool isrunning();

    // Lobby state
    // bool endstate() override;

    //~LobbyJoinSender();
};

#endif
