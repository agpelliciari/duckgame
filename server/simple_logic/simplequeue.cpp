#include "simplequeue.h"

#include <iostream>
#include <string>
#include <vector>

void SimpleQueue::notify(const PlayerActionDTO& action) {
    std::string name("Player_");
    name.append(std::to_string(action.playerind));
    if (action.type != PICK_UP) {
        std::cerr << "Invalid action!" << std::endl;
        return;
    }
    actions.push(SimpleAction(name, action.specific_info));
}

void SimpleQueue::close() { actions.close(); }

bool SimpleQueue::isopen() { return !actions.isclosed(); }

void SimpleQueue::applyOn(SimpleState& state) {
    // Popea todas las acciones a ejecutar. Se podria poner un limite al batch size.
    try {
        std::vector<SimpleAction> toexec = actions.pop_batch();
        for (auto actionit = toexec.begin(); actionit != toexec.end();) {
            actionit->applyOn(state);
            ++actionit;
        }
    } catch (const ClosedQueue& error) {
        std::cerr << ">closed match actions " << std::endl;
        return;
    }
}
