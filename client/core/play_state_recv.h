#ifndef PLAY_STATE_RECV_H
#define PLAY_STATE_RECV_H

#include "client/eventlistener.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/thread.h"


// El thread que basicamente notifica los cambios del protocolo al listener.
class PlayStateRecv: public Thread {

protected:
    ClientProtocol& protocol;  // cppcheck-suppress unusedStructMember
    EventListener& listener;   // cppcheck-suppress unusedStructMember
    GameContext& context;      // cppcheck-suppress unusedStructMember

public:
    explicit PlayStateRecv(ClientProtocol& _protocol, EventListener& _listener,
                           GameContext& _context);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    PlayStateRecv(const PlayStateRecv&) = delete;
    PlayStateRecv& operator=(const PlayStateRecv&) = delete;

    PlayStateRecv(PlayStateRecv&&) = delete;
    PlayStateRecv& operator=(PlayStateRecv&&) = delete;

    // Run para el thread corra cuando empieze.
    // Simplemente espera, en envia el evento
    void run() override;

    ~PlayStateRecv();
};

#endif
