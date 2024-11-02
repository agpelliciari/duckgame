#ifndef LOBBY_CREATE_SENDER_H
#define LOBBY_CREATE_SENDER_H

#include <string>

#include "./base_lobby_state.h"
#include "./lobby_client_sender.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/dtos.h"
#include "common/queue.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyCreateSender: public BaseLobbyState {
protected:
    LobbyClientSender sender;
    void run() override;

public:
    // Los default sin pasar por socket/protocol.
    explicit LobbyCreateSender(ClientProtocol& _protocol, GameContext& _context,
                               LobbyListener& _listener);

    LobbyCreateSender(LobbyCreateSender&&);
    LobbyCreateSender& operator=(LobbyCreateSender&&);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyCreateSender(const LobbyCreateSender&) = delete;
    LobbyCreateSender& operator=(const LobbyCreateSender&) = delete;

    LobbyClientSender& getSender();

    void createLobby();
};

#endif
