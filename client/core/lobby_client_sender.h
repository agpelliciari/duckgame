#ifndef LOBBY_CLIENT_SENDER_H
#define LOBBY_CLIENT_SENDER_H

#include <memory>
#include <string>

#include "./joinlobbymode.h"
#include "./lobbycreatemode.h"
#include "./lobbymode.h"
#include "client/gamecontext.h"
#include "client/menuhandler.h"
#include "common/clientprotocol.h"
#include "common/core/socket.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyClientSender: private Thread, public MenuHandler {
protected:
    ClientProtocol* protocol;         // cppcheck-suppress unusedStructMember
    std::unique_ptr<LobbyMode> mode;  // cppcheck-suppress unusedStructMember
    GameContext& context;             // cppcheck-suppress unusedStructMember
public:
    void joinLobby(uint8_t playercount, unsigned int idlobby) override;
    void createLobby(uint8_t playercount) override;
    void cancel() override;
    void doaction(const lobby_action& action) override;

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
