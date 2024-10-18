#ifndef LIB_Player_H
#define LIB_Player_H

#include <mutex>
#include <utility>

#include "common/event.h"
#include "common/queue.h"
#include "common/dtos.h"

typedef unsigned int player_id;
typedef Queue<MatchDto> player_events;


// La entidad player es un la parte logica que el match conoce.
// Tiene su id. Y sus eventos que se les notifico.
// Ademas de eso. Se considero pertinente poner un monitor/control del estado. Si esta abierto o no.
class Player {

protected:

    // Manejo de ids. Y cantidad de players para la queue de mensajes.
    uint8_t count;         // cppcheck-suppress unusedStructMember
    
    player_id ids[2];      // cppcheck-suppress unusedStructMember
    
    // For notifying actions and/or exit.
    player_events snapshots;  // cppcheck-suppress unusedStructMember

    bool _is_open;  // cppcheck-suppress unusedStructMember
    std::mutex mtx;

public:
    explicit Player();

    // Por ahora tambien nos escapamos del move.
    Player(Player&&) = delete;

    Player& operator=(Player&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    // No hace falta perse el operador se podria usar el getter de id.
    bool operator==(const Player& other) const;

    void setplayercount(const uint8_t count);
    uint8_t playercount() const ;
    
    // Seteado de id.
    void setid(const int ind, player_id id);
    player_id getid(const uint8_t ind) const;
    
    
    // Abre el jugador, indicando esta activo en una partida.
    bool open();

    // Desconecta/cierra el player. Si esta abierto.
    // Devuelve false si ya estaba cerrado.
    bool disconnect();

    // Checkea si el player sigue abierto, i.e no disconnected
    bool isopen();


    // recvevent es no bloqueante! Recibe el evento con try_push a la queue del player
    // Todo es "bloqueante" por posibles locks... pero bueno
    bool recvstate(const MatchDto& dto);

    // Pop event. Bloqueante. Si no hay eventos espera a uno.
    MatchDto popstate();
    
    //~Player();
};

#endif
