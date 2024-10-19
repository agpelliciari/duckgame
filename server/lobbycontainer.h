#ifndef LIB_LobbyContainer_H
#define LIB_LobbyContainer_H


#include <list>
#include <mutex>

#include "./match.h"

// Contenedor/monitor de los players activos en el match.
class LobbyContainer {
public:
    typedef std::list<Match> lobby_container;

private:
    lobbyID lastLobbyId;      // cppcheck-suppress unusedStructMember
    lobby_container lobbies;  // cppcheck-suppress unusedStructMember
    std::mutex mtx;

    Match& findLobby(lobbyID id);

public:
    // Default constructor
    LobbyContainer();
    // No copy nor mov.
    LobbyContainer(const LobbyContainer&) = delete;
    LobbyContainer& operator=(const LobbyContainer&) = delete;
    LobbyContainer(LobbyContainer&&) = delete;
    LobbyContainer& operator=(LobbyContainer&&) = delete;

    // Es necesrio trabajar con punteros al ser una coleccion
    Match& newLobby(Player* anfitrion);

    // Unirse a la lobby/match tira error si no existe. No espera a que se empieze.
    Match& joinLobby(Player* player, lobbyID id);

    // Una vez empezada no se aceptan mas.
    void startLobby(Match& match);

    void stopLobby(const Match& match);

    // Remueve todos los restantes. Normalmente no deberia haber, ya se deberian haber desconectado.
    void finishAll();
    ~LobbyContainer();
};

#endif
