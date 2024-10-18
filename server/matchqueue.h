#ifndef LIB_MatchQueue_H
#define LIB_MatchQueue_H

#include "../common_src/queue.h"
#include "./matchaction.h"
#include "./matchstate.h"


// Una clase media innecesaria capaz.
// Pero que tiene de logica el saber como aplicar las acciones en el state.
// Ademas de contenerlas, y definir si se aplica por batch y asi.
class MatchQueue {
private:
    Queue<MatchAction> actions;

public:
    void notify(const MatchAction& action);

    // Ademas de capaz poder usar el pop/ try_pop.
    // Como critical section no se deberia poder cerrar mientras se este iterando
    void applyOn(MatchState& state);

    void close();
};

#endif
