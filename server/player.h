#ifndef LIB_Player_H
#define LIB_Player_H

#include <mutex>
#include <utility>

#include "common/event.h"
#include "common/queue.h"
#include "./matchaction.h"

typedef unsigned int player_id;
typedef Queue<Event> player_events;


// La entidad player es un la parte logica que el match conoce.
// Tiene su id. Y sus eventos que se les notifico.
// Ademas de eso. Se considero pertinente poner un monitor/control del estado. Si esta abierto o no.
class Player {

protected:
    // For notifying actions and/or exit.
    player_id id;          // cppcheck-suppress unusedStructMember
    player_events events;  // cppcheck-suppress unusedStructMember

    bool _is_open;  // cppcheck-suppress unusedStructMember
    std::mutex mtx;

public:
    explicit Player(player_id ide);

    // Por ahora tambien nos escapamos del move.
    Player(Player&&) = delete;

    Player& operator=(Player&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    player_id getid() const;


    // No hace falta perse el operador se podria usar el getter de id.
    bool operator==(const Player& other) const;

    // Desconecta/cierra el player. Si esta abierto.
    // Devuelve false si ya estaba cerrado.
    bool disconnect();

    // Checkea si el player sigue abierto, i.e no disconnected
    bool isopen();

    // close libera/ cierra la queue, no se hace directamente en disconnect
    // ya que traeria mas complejidad para sincronizar/lockear
    void close();

    // recvevent es no bloqueante! Recibe el evento con try_push a la queue del player
    // Todo es "bloqueante" por posibles locks... pero bueno
    void recvevent(const Event& event);

    // Pop event. Bloqueante. Si no hay eventos espera a uno.
    Event popevent();
};

#endif
