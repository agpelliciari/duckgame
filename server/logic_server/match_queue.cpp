
#include "match_queue.h"

#include <iostream>

MatchQueue::MatchQueue(MatchLogic& match_logic_): queue(), match_logic(match_logic_) {}

void MatchQueue::push_command(const PlayerActionDTO& action) {
    // EL IND ES EL ID.. fue intercambiado en el receiver!.
    // std::cout << "OnMatchqueue from player:" << (int)action.playerind
    //          << " type: " << (int)action.type << std::endl;
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(ActionCommand(action, &this->match_logic));
}

bool MatchQueue::pop_command(ActionCommand& action) {
    std::unique_lock<std::mutex> lock(mutex);
    return queue.try_pop(action);
}


void MatchQueue::close() {}
