#ifndef Lobby_LISTENER_H
#define Lobby_LISTENER_H

#include "client/gamecontext.h"
#include "common/dtos.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyListener {
public:
    // Manejo de start/cancel una vez estando en una lobby.
    virtual void startedLobby() = 0;
    virtual void canceledLobby() = 0;

    // Notificacion inicial sobre si se pudo crear/unirse a una lobby.
    virtual void failedJoin() = 0;
    virtual void failedCreate() = 0;


    virtual void createdLobbyDual(const GameContext& context) = 0;
    virtual void createdLobbySolo(const GameContext& context) = 0;
    virtual void joinedLobbyDual(const GameContext& context) = 0;
    virtual void joinedLobbySolo(const GameContext& context) = 0;

    // Info general de respuesta/notificacion de algo.. configuracion o si joineo alguien y asi.
    virtual void notifyInfo(GameContext& context, const lobby_info& info) = 0;

    virtual ~LobbyListener() {}
};

#endif
