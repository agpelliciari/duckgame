#include "./simpleloop.h"

#include <iostream>

#include "unistd.h"


static const int SLEEP_TIME = 1000 * 200;  // 200ms

void SimpleLoop::loop(PlayerContainer& observer, SimpleQueue& actions) {
    while (actions.isopen()) {
        state.step();            // non player logic.
        actions.applyOn(state);  // player logic
        observer.updateState(state.getData());
        usleep(SLEEP_TIME);
    }
}
