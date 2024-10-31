#ifndef LIB_ControlledPlayer_H
#define LIB_ControlledPlayer_H

#include <mutex>
#include <string>
#include <utility>

#include "common/dtos.h"
#include "common/queue.h"
#include "server/logic_server/matchobserver.h"

typedef Queue<MatchDto> player_events;


// La entidad player es un la parte logica que el match conoce.
// Tiene su id. Y sus eventos que se les notifico.
// Ademas de eso. Se considero pertinente poner un monitor/control del estado. Si esta abierto o no.
class ControlledPlayer {

protected:
    bool _is_open;  // cppcheck-suppress unusedStructMember

    // Manejo de ids. Y cantidad de players para la queue de mensajes.
    uint8_t count;  // cppcheck-suppress unusedStructMember

    player_id ids[2];  // cppcheck-suppress unusedStructMember

    // For notifying actions and/or exit.
    player_events snapshots;  // cppcheck-suppress unusedStructMember

    std::mutex mtx;

public:
    explicit ControlledPlayer(player_id first);
    explicit ControlledPlayer(player_id first, player_id second);

    // Por ahora tambien nos escapamos del move.
    ControlledPlayer(ControlledPlayer&&) = delete;

    ControlledPlayer& operator=(ControlledPlayer&&) = delete;

    // Asumamos por ahora que no se quiere permitir copias
    ControlledPlayer(const ControlledPlayer&) = delete;
    ControlledPlayer& operator=(const ControlledPlayer&) = delete;


    // No hace falta perse el operador se podria usar el getter de id.
    bool operator==(const ControlledPlayer& other) const;

    uint8_t playercount() const;

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


    std::string toString();
    //~ControlledPlayer();
};

#endif
