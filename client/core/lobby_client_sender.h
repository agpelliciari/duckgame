#ifndef LOBBY_CLIENT_SENDER_H
#define LOBBY_CLIENT_SENDER_H

#include <memory>
#include <string>

#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/core/socket.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyClientSender: private Thread {
    // typedef std::unique_ptr<LobbyMode> lobby_mode;
    typedef void (LobbyClientSender::*lobby_runnable)();

protected:
    ClientProtocol* protocol;  // cppcheck-suppress unusedStructMember
    lobby_runnable mode;       // cppcheck-suppress unusedStructMember
    GameContext& context;      // cppcheck-suppress unusedStructMember
    uint8_t playercount;       // cppcheck-suppress unusedStructMember

    void handleJoin();
    void handleCreate();

public:
    void joinLobby(uint8_t playercount, unsigned int idlobby);
    void createLobby(uint8_t playercount);
    void cancel();
    void doaction(const lobby_action& action);

    // Los default sin pasar por socket/protocol.
    explicit LobbyClientSender(ClientProtocol& _protocol, GameContext& _context);

    LobbyClientSender(LobbyClientSender&&);
    LobbyClientSender& operator=(LobbyClientSender&&);


    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyClientSender(const LobbyClientSender&) = delete;
    LobbyClientSender& operator=(const LobbyClientSender&) = delete;


    bool isrunning();

    // void startJoinLobby(uint8_t playercount, unsigned int idlobby);
    // void startCreateLobby(uint8_t playercount);

    void run() override;

    int getcount();
    ~LobbyClientSender();
};

#endif
