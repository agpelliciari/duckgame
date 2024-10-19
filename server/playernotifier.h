#ifndef LIB_PlayerNotifier_H
#define LIB_PlayerNotifier_H

#include "./controlledplayer.h"
#include "./playerprotocol.h"
#include "common/thread.h"


// El thread que basicamente notifica de eventos al protocolo/client.
class PlayerNotifier: public Thread {

protected:
    ControlledPlayer& player;  // cppcheck-suppress unusedStructMember
    PlayerProtocol& protocol;  // cppcheck-suppress unusedStructMember

public:
    explicit PlayerNotifier(ControlledPlayer& _player, PlayerProtocol& protocol);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    PlayerNotifier(const PlayerNotifier&) = delete;
    PlayerNotifier& operator=(const PlayerNotifier&) = delete;

    PlayerNotifier(PlayerNotifier&&) = delete;
    PlayerNotifier& operator=(PlayerNotifier&&) = delete;

    // Run para el thread corra cuando empieze.
    // Simplemente espera, en envia el evento
    void run() override;
};

#endif
