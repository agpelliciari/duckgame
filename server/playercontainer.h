#ifndef LIB_PlayerContainer_H
#define LIB_PlayerContainer_H


#include <list>
#include <vector>

#include "./controlledplayer.h"
#include "common/dtos.h"

// Contenedor/monitor de los players activos en el match.
class PlayerContainer {
public:
    typedef std::list<ControlledPlayer*> player_container;

private:
    player_container players;  // cppcheck-suppress unusedStructMember
    player_id last_id;         // cppcheck-suppress unusedStructMember
public:
    // Default constructor
    PlayerContainer();
    // No copy nor mov.
    PlayerContainer(const PlayerContainer&) = delete;
    PlayerContainer& operator=(const PlayerContainer&) = delete;
    PlayerContainer(PlayerContainer&&) = delete;
    PlayerContainer& operator=(PlayerContainer&&) = delete;

    // Es necesrio trabajar con punteros al ser una coleccion
    void add(ControlledPlayer* player);

    // Remueve todos los restantes. Normalmente no deberia haber, ya se deberian haber desconectado.
    void removeAll();

    // Push/notifica eventos a los players, de forma no bloqueante! No tiene precondiciones perse
    // Devuelve los players que se desconectaron. Podrian ser notificados directamente
    std::vector<player_id> updateState(const MatchDto& state);
};

#endif
