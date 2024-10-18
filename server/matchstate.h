#ifndef LIB_MATCH_STATE_H
#define LIB_MATCH_STATE_H

#include <string>
#include <utility>

#include "common/event.h"
#include "common/queue.h"
#include "common/dtos.h"
#include "./box.h"

#define BOX_COUNT 4


// Clase encargada de la logica del match en si.
// Y que notifica los eventos.
class MatchState {
private:
    // fixed quantity of boxes, no enum needed for indexing.
    Box boxes[BOX_COUNT];  // cppcheck-suppress unusedStructMember

protected:
    // Verify if box is available.
    bool isBoxAvailable(int box) const;

public:
    explicit MatchState() {}

    // Asumamos copy = default, move = default
    MatchState(const MatchState&) = delete;
    MatchState& operator=(const MatchState&) = delete;
    MatchState(MatchState&&) = delete;
    MatchState& operator=(MatchState&&) = delete;

    // Avanza un paso de tiempo, notifica al observer los eventos ocurridos.
    // Aca en teoria ocurririan los non player events.
    void step();

    // Intenta que el player abra la caja. Notifica el evento de ocurrir.
    void openBox(const std::string& player, const int box);
    
    MatchDto getData() const ;
};

#endif
