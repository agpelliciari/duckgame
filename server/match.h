#ifndef LIB_MATCH_H
#define LIB_MATCH_H

#include <mutex>
#include <queue>
#include <utility>

#include "common/event.h"
#include "common/thread.h"
#include "./matchaction.h"
#include "./matchqueue.h"
#include "./matchstate.h"
#include "./playercontainer.h"

// Clase para encapsular la logica de lopeado. De forma asincrona.
// Delega el manejo del estado, notificado de eventos y recepcion de acciones
class Match: private Thread {
private:
    PlayerContainer& players;
    MatchState state;    // cppcheck-suppress unusedStructMember
    MatchQueue actions;  // cppcheck-suppress unusedStructMember

public:
    // Se tendra composicion con un unico observer de eventos al match.
    explicit Match(PlayerContainer& _players);

    // Asumamos por ahora que no se quiere permitir copias, ni mov.
    Match(const Match&) = delete;
    Match& operator=(const Match&) = delete;

    Match(Match&&) = delete;
    Match& operator=(Match&&) = delete;

    // No hay precondiciones perse. Podria no haber empezado el match.
    // Metodos delegatorios
    void notifyAction(const MatchAction&& action);
    
    // Para el thread y en general el loopeado
    void run() override;

    // Metodos analogos a los de thread.
    void init();
    bool isrunning();

    // Libera, bien podria prescindirse y usar un destructor.
    // Pero mejor explicitar. Reemplaza el stop.. que no se quiere permitir hacerlo sin hacer el
    // resto.
    void finish();

    ~Match();
};

#endif
