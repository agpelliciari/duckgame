#ifndef GAME_ACTION_SENDER_H
#define GAME_ACTION_SENDER_H

#include <memory>
#include <string>

#include "./lobby_state.h"
#include "client/actionlistener.h"
#include "client/eventlistener.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/dtos.h"
#include "common/queue.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class GameActionSender: private Thread, public ActionListener, public LobbyState {
protected:
    ClientProtocol& protocol;  // cppcheck-suppress unusedStructMember
    EventListener& listener;
    GameContext& context;
    bool firstidle;   // cppcheck-suppress unusedStructMember
    bool secondidle;  // cppcheck-suppress unusedStructMember

    Queue<PlayerActionDTO> actions;


public:
    void doaction(const PlayerActionDTO& action) override;
    void disconnect() override;

    // Los default sin pasar por socket/protocol.
    explicit GameActionSender(ClientProtocol& _protocol, EventListener& _listener,
                              GameContext& _context);

    // GameActionSender(GameActionSender&&);
    // GameActionSender& operator=(GameActionSender&&);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    GameActionSender(const GameActionSender&) = delete;
    GameActionSender& operator=(const GameActionSender&) = delete;


    void begin();

    void end();

    bool isrunning();

    // void startJoinLobby(uint8_t playercount, unsigned int idlobby);
    // void startCreateLobby(uint8_t playercount);

    void run() override;

    int getcount();

    bool endstate() override;

    ~GameActionSender();
};

#endif
