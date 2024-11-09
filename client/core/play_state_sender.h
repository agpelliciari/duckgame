#ifndef PLAY_STATE_SENDER_H
#define PLAY_STATE_SENDER_H

#include <string>

#include "./game_state.h"
#include "client/actionlistener.h"
#include "client/eventlistener.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/queue.h"
#include "common/thread.h"

// El encapsulador del play state, donde se esta escuchando por acciones
// Que se mandaran al match en el server, en el thread separado.
// En el thread del sender tambien se lanza paralelamente el thread recibidor.

class PlayStateSender: private Thread, public ActionListener, public GameState {
protected:
    ClientProtocol protocol;  // cppcheck-suppress unusedStructMember
    EventListener& listener;
    GameContext& context;
    bool firstidle;   // cppcheck-suppress unusedStructMember
    bool secondidle;  // cppcheck-suppress unusedStructMember

    Queue<PlayerActionDTO> actions;

    void run() override;

public:
    void doaction(const PlayerActionDTO& action) override;
    void disconnect() override;

    // Los default sin pasar por socket/protocol.
    explicit PlayStateSender(Messenger& _messenger, EventListener& _listener,
                             GameContext& _context);

    PlayStateSender(PlayStateSender&&) = delete;
    PlayStateSender& operator=(PlayStateSender&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    PlayStateSender(const PlayStateSender&) = delete;
    PlayStateSender& operator=(const PlayStateSender&) = delete;


    void begin();

    void end();

    bool isrunning();

    bool endstate() override;

    ~PlayStateSender();
};

#endif
