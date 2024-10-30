#ifndef LOBBY_CLIENT_SENDER_H
#define LOBBY_CLIENT_SENDER_H

#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>

#include "./lobby_state.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/core/socket.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyClientSender: private Thread, public LobbyState {
    // typedef std::unique_ptr<LobbyMode> lobby_mode;
    typedef void (LobbyClientSender::*lobby_runnable)();

protected:
    ClientProtocol& protocol;  // cppcheck-suppress unusedStructMember
    lobby_runnable mode;       // cppcheck-suppress unusedStructMember
    GameContext& context;      // cppcheck-suppress unusedStructMember

    std::mutex mtx;
    std::condition_variable started_lobby;

    void handleJoin();
    void handleCreate();

    void waitStart();

public:
    void joinLobby(bool dualplay, unsigned int idlobby);
    void createLobby(bool dualplay);
    void cancel();
    void doaction(const lobby_action& action);

    // Los default sin pasar por socket/protocol.
    explicit LobbyClientSender(ClientProtocol& _protocol, GameContext& _context);

    LobbyClientSender(LobbyClientSender&&);
    LobbyClientSender& operator=(LobbyClientSender&&);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyClientSender(const LobbyClientSender&) = delete;
    LobbyClientSender& operator=(const LobbyClientSender&) = delete;


    void notifyStart();
    bool isrunning();

    // void startJoinLobby(uint8_t playercount, unsigned int idlobby);
    // void startCreateLobby(uint8_t playercount);

    void run() override;

    int getcount();

    // Lobby state
    bool endstate() override;

    ~LobbyClientSender();
};

#endif
