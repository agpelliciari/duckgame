#ifndef LOBBY_CREATE_STATE_H
#define LOBBY_CREATE_STATE_H

#include <string>

#include "./lobby_action_queue.h"
#include "./lobby_state_recv.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/queue.h"

// GameState para la creacion de una lobby,
// que comparte la parte de recibir info de la lobby del server.
class LobbyCreateState: public LobbyStateRecv {
protected:
    LobbyActionQueue sender;
    void run() override;
    bool checkcreatefail();

public:
    explicit LobbyCreateState(Messenger& _messenger, GameContext& _context,
                              LobbyListener& _listener);

    LobbyCreateState(LobbyCreateState&&) = delete;
    LobbyCreateState& operator=(LobbyCreateState&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyCreateState(const LobbyCreateState&) = delete;
    LobbyCreateState& operator=(const LobbyCreateState&) = delete;

    // No es ideal. Pero por ahora que se decidio el state perse
    // Sea el receiver de info, la queue del sender que tiene el mismo scope.
    // Se guarda en el receiver. Y se expone para el menu.
    LobbyActionQueue& getSender();

    // Inicia el thread, y hace lo necesario para que se cree la partida.
    void createLobby();
    ~LobbyCreateState();
};

#endif
