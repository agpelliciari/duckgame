#include "matchqueue.h"

#include <iostream>
#include <vector>

void MatchQueue::notify(const MatchAction& action) { actions.push(action); }
void MatchQueue::close() { actions.close(); }

void MatchQueue::applyOn(MatchState& state) {
    // Popea todas las acciones a ejecutar. Se podria poner un limite al batch size.
    try {
        std::vector<MatchAction> toexec = actions.pop_batch();
        for (auto actionit = toexec.begin(); actionit != toexec.end();) {
            actionit->applyOn(state);
            ++actionit;
        }
    } catch (const ClosedQueue& error) {
        std::cerr << ">closed match actions " << std::endl;
        return;
    }
}
