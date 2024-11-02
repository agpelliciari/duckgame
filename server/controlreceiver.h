#ifndef LIB_ControlReceiver_H
#define LIB_ControlReceiver_H


#include "./controlledplayer.h"
#include "./lobbycontainer.h"
#include "./match.h"
#include "common/core/socket.h"
#include "common/serverprotocol.h"
#include "common/thread.h"

// ControlledPlayer controller va a ser el thread recibidor de un protocol.
// Va a pertenecer a un match. Y va a tener el ownership la entidad en el juego. El player.
// El player controller tiene el ownership del player, entidad del juego.
// Aun asi es preferible que el monitor de players se encarge perse de cerrarlos(las queues). Asi es
// thread safe.
class ControlReceiver: private Thread {

protected:
    LobbyContainer& lobbies;  // cppcheck-suppress unusedStructMember
    ServerProtocol protocol;

    bool playOn(const ControlledPlayer& player, Match& match);

public:
    // Crea el player con el ide pasado e inicia el protocolo
    explicit ControlReceiver(LobbyContainer& _lobbies, Socket& skt);

    // Por ahora tambien nos escapamos del move.
    ControlReceiver(ControlReceiver&&) = delete;
    ControlReceiver& operator=(ControlReceiver&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    ControlReceiver(const ControlReceiver&) = delete;
    ControlReceiver& operator=(const ControlReceiver&) = delete;


    // Starts thread. And receive/notifies actions.
    void run() override;

    // Reemplazos para lo que normalmente seria de thread.
    // Con logica extra para tener en cuenta el notifier.

    // Como el isalive pero compartido entre receiver/notifier
    bool isopen();

    // Conceptualmente como start/stop pero tambien toma inicia/termina
    // el notifier.
    void init();
    void finish();

    ~ControlReceiver();
};

#endif
