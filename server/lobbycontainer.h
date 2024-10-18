#ifndef LIB_LobbyContainer_H
#define LIB_LobbyContainer_H


#include <list>
#include <mutex>
#include "./lobby.h"

// Contenedor/monitor de los players activos en el match.
class LobbyContainer {
public:
    typedef std::list<Lobby> lobby_container;

private:
    lobbyID lastLobbyId;  // cppcheck-suppress unusedStructMember
    lobby_container lobbies;  // cppcheck-suppress unusedStructMember
    std::mutex mtx;
    
    Lobby& findLobby(lobbyID id);
public:
    // Default constructor
    LobbyContainer();
    // No copy nor mov.
    LobbyContainer(const LobbyContainer&) = delete;
    LobbyContainer& operator=(const LobbyContainer&) = delete;
    LobbyContainer(LobbyContainer&&) = delete;
    LobbyContainer& operator=(LobbyContainer&&) = delete;

    // Es necesrio trabajar con punteros al ser una coleccion
    lobbyID newLobby(Player* anfitrion);
    
    // Unirse a la lobby y esperar a que empieze la partida. Tira error si no existe.
    Match& joinLobby(Player* player, lobbyID id);
    
    // Una vez empezada no se aceptan mas.
    Match& startLobby(lobbyID id);
    
    void stopLobby(lobbyID id);

    // Remueve todos los restantes. Normalmente no deberia haber, ya se deberian haber desconectado.
    void finishAll();
    ~LobbyContainer();

};

#endif
