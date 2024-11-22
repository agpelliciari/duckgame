#ifndef LIB_LobbyContainer_H
#define LIB_LobbyContainer_H


#include <list>
#include <vector>
#include <string>
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

    // Unirse a la lobby/match tira error si no existe. No espera a que se empieze.
    Match& findLobby(lobbyID id);
public:
    // Default constructor
    LobbyContainer();
    LobbyContainer(const char* maps_root);
    
    // No copy nor mov.
    LobbyContainer(const LobbyContainer&) = delete;
    LobbyContainer& operator=(const LobbyContainer&) = delete;
    LobbyContainer(LobbyContainer&&) = delete;
    LobbyContainer& operator=(LobbyContainer&&) = delete;

    const std::vector<std::string>& registeredMaps() const;
    
    // Acciones para create vs join lobby. Encapsuladas en un metodo
    // con el join de players para hacerlo thread safe.
    Match& newLobby(ControlId& out);
    Match& joinLobby(lobbyID id, ControlId& out, std::vector<player_id>& players);
    
    
    int countMatches();
    int countPlayers(Match& match);

    // Una vez empezada no se aceptan mas.
    void startLobby(Match& match, const char* mapname);


    ControlledPlayer& getPlayerOn(Match& match, const ControlId& id);
    void disconnectFrom(Match& match, ControlledPlayer& player);

    // Si se esta en la lobby y el anfitrion se va. Se cancela.
    void hostLeft(Match& match, ControlledPlayer& host);
    void errorOnLobby(Match& match, LobbyErrorType error);

    // Remueve todos los restantes. Normalmente no deberia haber, ya se deberian haber desconectado.
    void finishAll();
    ~LobbyContainer();
};

#endif
