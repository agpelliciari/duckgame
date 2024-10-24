#ifndef CREATE_LOBBY_MODE_H
#define CREATE_LOBBY_MODE_H

#include <cstdint>

#include "client/lobbymode.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyCreateMode: public LobbyMode {
private:
    uint8_t playercount;  // cppcheck-suppress unusedStructMember
public:
    explicit LobbyCreateMode(uint8_t _playercount);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyCreateMode(const LobbyCreateMode&) = delete;
    LobbyCreateMode& operator=(const LobbyCreateMode&) = delete;

    LobbyCreateMode(LobbyCreateMode&&) = delete;
    LobbyCreateMode& operator=(LobbyCreateMode&&) = delete;


    void startLobby();
    void exec(ClientProtocol& protocol) override;
};

#endif
