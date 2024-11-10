#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

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

// El game manager se encarga de conectar al server
// Y mantener la referencia al estado actual, que es el que hace realmente cosas
// Con la conexion, por ahora existiendo dos fases principales
// la fase Lobby y la fase Play.
class GameManager {
protected:
    GameContext& context;  // cppcheck-suppress unusedStructMember

    std::optional<Socket> skt;         // cppcheck-suppress unusedStructMember
    std::unique_ptr<GameState> state;  // cppcheck-suppress unusedStructMember

    std::string hostname;  // cppcheck-suppress unusedStructMember
    std::string service;   // cppcheck-suppress unusedStructMember

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
