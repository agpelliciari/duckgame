#ifndef LIB_PlayerController_H
#define LIB_PlayerController_H


#include "common/socket.h"
#include "common/thread.h"
#include "./lobbycontainer.h"
#include "./match.h"
#include "./controlledplayer.h"
#include "./playerprotocol.h"

// ControlledPlayer controller va a ser el thread recibidor de un protocol.
// Va a pertenecer a un match. Y va a tener el ownership la entidad en el juego. El player.
// El player controller tiene el ownership del player, entidad del juego.
// Aun asi es preferible que el monitor de players se encarge perse de cerrarlos(las queues). Asi es
// thread safe.
class PlayerController: private Thread {

protected:
    LobbyContainer& lobbies;   // cppcheck-suppress unusedStructMember
    PlayerProtocol protocol;    
    void playOn(ControlledPlayer& player, Match& match);
    void handleNewLobby(const uint8_t countplayers);
public:
    // Crea el player con el ide pasado e inicia el protocolo
    explicit PlayerController(LobbyContainer& _lobbies, Socket& skt);

    // Por ahora tambien nos escapamos del move.
    PlayerController(PlayerController&&) = delete;
    PlayerController& operator=(PlayerController&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    PlayerController(const PlayerController&) = delete;
    PlayerController& operator=(const PlayerController&) = delete;


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

    ~PlayerController();
};

#endif
