#include "./simpleeventlistener.h"

#include <iostream>

SimpleEventListener::SimpleEventListener() {}

void SimpleEventListener::matchUpdated(const MatchDto& state) {
    std::cout << "MATCH STATE " << &state << std::endl;
}
void SimpleEventListener::matchFinished(const MatchDto& final_info) {
    std::cout << "MATCH FINISHED " << &final_info << std::endl;
}

SimpleEventListener::~SimpleEventListener() {}
