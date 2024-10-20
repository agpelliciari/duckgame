#ifndef LIB_SIMPLE_LOOP_H
#define LIB_SIMPLE_LOOP_H

#include <string>
#include <utility>

#include "common/dtos.h"
#include "server/playercontainer.h"
#include "server/simple_logic/simplequeue.h"
#include "server/simple_logic/simplestate.h"

#define BOX_COUNT 4


// Clase encargada de la logica del match en si.
// Y que notifica los eventos.
class SimpleLoop {
private:
    SimpleState state;

public:
    SimpleLoop() {}

    // Asumamos copy = default, move = default
    SimpleLoop(const SimpleLoop&) = delete;
    SimpleLoop& operator=(const SimpleLoop&) = delete;
    SimpleLoop(SimpleLoop&&) = delete;
    SimpleLoop& operator=(SimpleLoop&&) = delete;

    void loop(PlayerContainer& observer, SimpleQueue& actions);
};

#endif
