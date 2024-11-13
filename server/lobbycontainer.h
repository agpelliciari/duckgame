#ifndef LIB_LobbyContainer_H
#define LIB_LobbyContainer_H


#include <list>
#include <mutex>

#include "./match.h"
#include "serial/map_loader.h"

// Contenedor/monitor de los players activos en el match.
class LobbyContainer {
public:
    typedef std::list<Match> lobby_container;

private:
    lobbyID lastLobbyId;  // cppcheck-suppress unusedStructMember
    MapLoader maps;
    lobby_container lobbies;  // cppcheck-suppress unusedStructMember
    std::mutex mtx;

public:
    // Default constructor
    LobbyContainer();
    // No copy nor mov.
    LobbyContainer(const LobbyContainer&) = delete;
    LobbyContainer& operator=(const LobbyContainer&) = delete;
    LobbyContainer(LobbyContainer&&) = delete;
    LobbyContainer& operator=(LobbyContainer&&) = delete;

    // Es necesrio trabajar con punteros al ser una coleccion
    Match& newLobby();

    // Unirse a la lobby/match tira error si no existe. No espera a que se empieze.
    Match& findLobby(lobbyID id);

    ControlledPlayer& joinLobby(uint8_t count, Match& match);

    int countMatches();

    // Una vez empezada no se aceptan mas.
    void startLobby(Match& match, const char* mapname);


    void disconnectFrom(Match& match, ControlledPlayer& player);

    // Si se esta en la lobby y el anfitrion se va. Se cancela.
    void hostLeft(Match& match, ControlledPlayer& host);
    void errorOnLobby(Match& match, LobbyErrorType error);

    // Remueve todos los restantes. Normalmente no deberia haber, ya se deberian haber desconectado.
    void finishAll();
    ~LobbyContainer();
};

#endif
