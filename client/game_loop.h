#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <memory>
#include <string>

#include "./joinlobbymode.h"
#include "./lobbycreatemode.h"
#include "./lobbymode.h"
#include "common/clientprotocol.h"
#include "common/core/socket.h"
#include "common/thread.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class GameLoop: private Thread {
protected:
    ClientProtocol protocol;          // cppcheck-suppress unusedStructMember
    std::unique_ptr<LobbyMode> mode;  // cppcheck-suppress unusedStructMember

    unsigned int inputnum();

    void sendMove(char action);

public:
    // Los default sin pasar por socket/protocol.
    explicit GameLoop(const char* host, const char* service);
    explicit GameLoop(const char* service);
    // Permitamos el mov desde uno existente para mayor flexibilidad?
    explicit GameLoop(Protocol&& prot);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;

    GameLoop(GameLoop&&) = delete;
    GameLoop& operator=(GameLoop&&) = delete;


    bool isrunning();

    void startJoinLobby(uint8_t playercount, unsigned int idlobby);
    void startCreateLobby(uint8_t playercount);

    void run() override;

    int getcount();
    ~GameLoop();
};

#endif
