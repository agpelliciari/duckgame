#ifndef LOBBY_CREATE_SENDER_H
#define LOBBY_CREATE_SENDER_H

#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>

#include "./lobby_client_sender.h"
#include "./lobby_listener.h"
#include "./lobby_state.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/core/socket.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyCreateSender: private Thread, public LobbyState, public LobbyClientSender {
protected:
    ClientProtocol& protocol;  // cppcheck-suppress unusedStructMember
    GameContext& context;      // cppcheck-suppress unusedStructMember

    bool started_match;       // cppcheck-suppress unusedStructMember
    LobbyListener& listener;  // cppcheck-suppress unusedStructMember

    std::mutex mtx;
    std::condition_variable match_start;

    void waitStart();
    void run() override;

public:
    // Los default sin pasar por socket/protocol.
    explicit LobbyCreateSender(ClientProtocol& _protocol, GameContext& _context,
                               LobbyListener& _listener);

    LobbyCreateSender(LobbyCreateSender&&);
    LobbyCreateSender& operator=(LobbyCreateSender&&);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyCreateSender(const LobbyCreateSender&) = delete;
    LobbyCreateSender& operator=(const LobbyCreateSender&) = delete;

    void createLobby();
    void notifyCancel();

    void doaction(const lobby_action& action) override;
    void notifyStart() override;
    bool isrunning() override;

    // Lobby state
    bool endstate() override;

    ~LobbyCreateSender();
};

#endif
