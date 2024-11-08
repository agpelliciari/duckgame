#ifndef BASE_LOBBY_SENDER_H
#define BASE_LOBBY_SENDER_H


#include "client/core/game_state.h"
#include "client/core/lobby_listener.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyStateRecv: protected Thread, public GameState {


protected:
    // cppcheck-suppress unusedStructMember
    static const char* ERRORS[];

    ClientProtocol protocol;  // cppcheck-suppress unusedStructMember
    GameContext& context;     // cppcheck-suppress unusedStructMember
    LobbyListener& listener;  // cppcheck-suppress unusedStructMember

    void handleNotify(const lobby_info& info);
    void listeninfo();

public:
    // Los default sin pasar por socket/protocol.
    explicit LobbyStateRecv(Messenger& _messenger, GameContext& _context, LobbyListener& _listener);

    LobbyStateRecv(LobbyStateRecv&&) = delete;
    LobbyStateRecv& operator=(LobbyStateRecv&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyStateRecv(const LobbyStateRecv&) = delete;
    LobbyStateRecv& operator=(const LobbyStateRecv&) = delete;

    // Lobby state
    bool endstate() override;

    virtual ~LobbyStateRecv();
};

#endif
