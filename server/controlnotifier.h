#ifndef LIB_ControlNotifier_H
#define LIB_ControlNotifier_H

#include "./controlledplayer.h"
#include "./match.h"
#include "common/serverprotocol.h"
#include "common/thread.h"


// El thread que basicamente notifica de eventos al protocolo/client.
class ControlNotifier: public Thread {

protected:
    Match& match;              // cppcheck-suppress unusedStructMember
    ControlledPlayer& player;  // cppcheck-suppress unusedStructMember
    ServerProtocol& protocol;  // cppcheck-suppress unusedStructMember

    bool runLobby();
    MatchStateType runGame();
    
    bool runPostGame(MatchStateType state);
public:
    explicit ControlNotifier(Match& match, ControlledPlayer& _player, ServerProtocol& protocol);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    ControlNotifier(const ControlNotifier&) = delete;
    ControlNotifier& operator=(const ControlNotifier&) = delete;

    ControlNotifier(ControlNotifier&&) = delete;
    ControlNotifier& operator=(ControlNotifier&&) = delete;

    // Run para el thread corra cuando empieze.
    // Simplemente espera, en envia el evento
    void run() override;

    ~ControlNotifier();
};

#endif
