#ifndef GAME_LOOP_H
#define GAME_LOOP_H

//#include "common/core/socket.h"
//#include <memory>
#include <string>

//#include "./joinlobbymode.h"
//#include "./lobbycreatemode.h"
//#include "./lobbymode.h"
//#include "common/thread.h"

#include "./game_action_sender.h"
#include "./lobby_client_sender.h"
#include "client/eventlistener.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class GameLoop {
protected:
    ClientProtocol protocol;  // cppcheck-suppress unusedStructMember
public:
    // Los default sin pasar por socket/protocol.
    explicit GameLoop(const char* host, const char* service);
    explicit GameLoop(const char* service);
    // Permitamos el mov desde uno existente para mayor flexibilidad?
    explicit GameLoop(Protocol&& prot);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;

    GameLoop(GameLoop&&) = delete;
    GameLoop& operator=(GameLoop&&) = delete;

    LobbyClientSender initLobbyClient(GameContext& context);
    GameActionSender initGame(EventListener& listener);
    ~GameLoop();
};

#endif
