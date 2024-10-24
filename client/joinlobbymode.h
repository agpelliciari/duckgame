#ifndef JOIN_LOBBY_MODE_H
#define JOIN_LOBBY_MODE_H

#include <cstdint>

#include "client/lobbymode.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class JoinLobbyMode: public LobbyMode {
private:
    uint8_t playercount;  // cppcheck-suppress unusedStructMember
    uint8_t idlobby;      // cppcheck-suppress unusedStructMember
public:
    explicit JoinLobbyMode(uint8_t _count, uint8_t id);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    JoinLobbyMode(const JoinLobbyMode&) = delete;
    JoinLobbyMode& operator=(const JoinLobbyMode&) = delete;

    JoinLobbyMode(JoinLobbyMode&&) = delete;
    JoinLobbyMode& operator=(JoinLobbyMode&&) = delete;

    void exec(ClientProtocol& protocol) override;
};

#endif
