#ifndef LOBBY_STATE_RECV_H
#define LOBBY_STATE_RECV_H


#include "client/core/game_state.h"
#include "client/core/lobby_listener.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/thread.h"


// Base para los states de lobby que recibe la info del server y se la
// notifica al listener.
class LobbyStateRecv: protected Thread, public GameState {
protected:
    // cppcheck-suppress unusedStructMember
    static const char* ERRORS[];
    static const char CLIENT_CONN_ERROR[];  // cppcheck-suppress unusedStructMember

    ClientProtocol protocol;  // cppcheck-suppress unusedStructMember
    GameContext& context;     // cppcheck-suppress unusedStructMember
    LobbyListener& listener;  // cppcheck-suppress unusedStructMember

    void handleNotify(const lobby_info& info);
    lobby_info listenUntilLobbyEnd();

    //void setInitedMatch(int totalplayers);
    void setInitedMatch();

public:
    explicit LobbyStateRecv(Messenger& _messenger, GameContext& _context, LobbyListener& _listener);

    LobbyStateRecv(LobbyStateRecv&&) = delete;
    LobbyStateRecv& operator=(LobbyStateRecv&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyStateRecv(const LobbyStateRecv&) = delete;
    LobbyStateRecv& operator=(const LobbyStateRecv&) = delete;

    // Termina forzosamente de ser necesario y retorna si deberia continuar al play state.
    bool endstate() override;

    virtual ~LobbyStateRecv();
};

#endif
