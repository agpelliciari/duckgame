#ifndef LIB_PlayerContainer_H
#define LIB_PlayerContainer_H


#include <list>
#include <mutex>

#include "common/event.h"
#include "./matchobserver.h"
#include "./player.h"

// Contenedor/monitor de los players activos en el match.
class PlayerContainer: public MatchObserver {
public:
    typedef std::list<Player*> player_container;

private:
    player_container players;  // cppcheck-suppress unusedStructMember

    std::mutex mtx;

public:
    // Default constructor
    PlayerContainer();
    // No copy nor mov.
    PlayerContainer(const PlayerContainer&) = delete;
    PlayerContainer& operator=(const PlayerContainer&) = delete;
    PlayerContainer(PlayerContainer&&) = delete;
    PlayerContainer& operator=(PlayerContainer&&) = delete;

    // Es necesrio trabajar con punteros al ser una coleccion
    void add(Player* player);

    // Ademas del remove en si, cierra el player. Se hace aca para hacerlo thread safe.
    void remove(Player* player);

    // Remueve todos los restantes. Normalmente no deberia haber, ya se deberian haber desconectado.
    void removeAll();

    // Push/notifica eventos a los players, de forma no bloqueante! No tiene precondiciones perse
    // Aunque podria ser medianamente bloqueante, ya que las queues de los players son thread safe.
    void receiveEvent(const Event&& event) override;
};

#endif
