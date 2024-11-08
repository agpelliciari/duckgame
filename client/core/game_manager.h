#ifndef GAME_LOOP_H
#define GAME_LOOP_H

//#include "common/core/socket.h"

#include <memory>
#include <optional>
#include <string>

#include "./lobby_listener.h"
#include "./play_state_sender.h"
#include "client/eventlistener.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/core/socket.h"
#include "lobby/lobby_action_queue.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class GameManager {
protected:
    GameContext& context;  // cppcheck-suppress unusedStructMember

    std::optional<Socket> skt;  // cppcheck-suppress unusedStructMember
    std::string hostname;       // cppcheck-suppress unusedStructMember
    std::string service;        // cppcheck-suppress unusedStructMember

    std::unique_ptr<GameState> state;  // cppcheck-suppress unusedStructMember
public:
    explicit GameManager(GameContext& _context);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    GameManager(GameManager&&) = delete;
    GameManager& operator=(GameManager&&) = delete;

    void setHostnamePort(const std::string& newhost, const std::string& newservice);

    void clear();
    // Resetea el estado al inicial.
    bool reset();

    // Verifica dado el estado actual, si deberia exitear.
    // O se podria ir a un siguiente estado.
    bool cangonext();

    // Setea el estado para el manejo de lobby
    LobbyActionQueue* setLobbyCreator(LobbyListener& listener, bool dual);
    void setLobbyJoin(LobbyListener& listener, bool dual, unsigned int lobbyid);

    // Setea el estado para el inicio del juego.
    PlayStateSender* initGame(EventListener& listener);

    ~GameManager();


    // Getters del contexto.

    int getTotalPlayers() const;
    bool isdual() const;
};

#endif
