#ifndef LIB_PlayerNotifier_H
#define LIB_PlayerNotifier_H

#include "common/thread.h"
#include "./player.h"
#include "./playerprotocol.h"


// El thread que basicamente notifica de eventos al protocolo/client.
class PlayerNotifier: public Thread {

protected:
    Player& player;            // cppcheck-suppress unusedStructMember
    PlayerProtocol& protocol;  // cppcheck-suppress unusedStructMember

public:
    explicit PlayerNotifier(Player& _player, PlayerProtocol& protocol);

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
