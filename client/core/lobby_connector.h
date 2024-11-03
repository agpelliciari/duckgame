#ifndef GAME_LOOP_H
#define GAME_LOOP_H

//#include "common/core/socket.h"

#include <memory>
#include <optional>
#include <string>

#include "./game_action_sender.h"
#include "./lobby_client_sender.h"
#include "./lobby_listener.h"
#include "client/eventlistener.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "common/core/socket.h"

// Clase que encapsula al protocol y mantendria el estado del juego
// Proporcionado una interfaz para acciones del usuario.
class LobbyConnector {
protected:
    GameContext& context;  // cppcheck-suppress unusedStructMember

    std::optional<Socket> skt;  // cppcheck-suppress unusedStructMember
    std::string hostname;       // cppcheck-suppress unusedStructMember
    std::string service;        // cppcheck-suppress unusedStructMember

    std::unique_ptr<LobbyState> state;  // cppcheck-suppress unusedStructMember
public:
    explicit LobbyConnector(GameContext& _context);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    LobbyConnector(const LobbyConnector&) = delete;
    LobbyConnector& operator=(const LobbyConnector&) = delete;

    LobbyConnector(LobbyConnector&&) = delete;
    LobbyConnector& operator=(LobbyConnector&&) = delete;

    void setHostnamePort(const std::string& newhost, const std::string& newservice);

    void clear();
    // Resetea el estado al inicial.
    void reset();

    // Verifica dado el estado actual, si deberia exitear.
    // O se podria ir a un siguiente estado.
    bool cangonext();

    // Setea el estado para el manejo de lobby
    LobbyClientSender* setLobbyCreator(LobbyListener& listener, bool dual);
    void setLobbyJoin(LobbyListener& listener, bool dual, unsigned int lobbyid);

    // Setea el estado para el inicio del juego.
    GameActionSender* initGame(EventListener& listener);

    ~LobbyConnector();


    // Getters del contexto.

    int getTotalPlayers() const;
    bool isdual() const;
};

#endif
