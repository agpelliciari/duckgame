#ifndef GAME_STATE_RECV_H
#define GAME_STATE_RECV_H

#include "client/eventlistener.h"
#include "common/clientprotocol.h"
#include "common/thread.h"


// El thread que basicamente notifica de eventos al protocolo/client.
class GameStateRecv: public Thread {

protected:
    ClientProtocol& protocol;  // cppcheck-suppress unusedStructMember
    EventListener& listener;   // cppcheck-suppress unusedStructMember

public:
    explicit GameStateRecv(ClientProtocol& _protocol, EventListener& _listener);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    GameStateRecv(const GameStateRecv&) = delete;
    GameStateRecv& operator=(const GameStateRecv&) = delete;

    GameStateRecv(GameStateRecv&&) = delete;
    GameStateRecv& operator=(GameStateRecv&&) = delete;

    // Run para el thread corra cuando empieze.
    // Simplemente espera, en envia el evento
    void run() override;

    ~GameStateRecv();
};

#endif
