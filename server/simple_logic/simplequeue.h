#ifndef LIB_SimpleQueue_H
#define LIB_SimpleQueue_H

#include "common/queue.h"
#include "common/dtosplayer.h"
#include "./simplestate.h"
#include "./simpleaction.h"


// Una clase media innecesaria capaz.
// Pero que tiene de logica el saber como aplicar las acciones en el state.
// Ademas de contenerlas, y definir si se aplica por batch y asi.
class SimpleQueue {
private:
    Queue<SimpleAction> actions;

public:
    void notify(const PlayerActionDTO& action);

    // Ademas de capaz poder usar el pop/ try_pop.
    // Como critical section no se deberia poder cerrar mientras se este iterando
    void applyOn(SimpleState& state);

    void close();
};

#endif
