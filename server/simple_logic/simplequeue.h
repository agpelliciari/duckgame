#ifndef LIB_SIMPLE_QUEUE_H
#define LIB_SIMPLE_QUEUE_H

#include "./simpleaction.h"
#include "./simplestate.h"
#include "common/dtosplayer.h"
#include "common/queue.h"


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
    bool isopen();

    void close();
};

#endif
