
#include "./match_state.h"

MatchState::MatchState(MatchLogic &match_logic_):running(true), match_logic(match_logic_){}

void MatchState::loop(/*PlayerContainer& observer, */MatchQueue& acciones) {
    while (running){
        this->receive_commands(acciones);
        this->execute_commands();
        this->send_results();
    }
}

void MatchState::receive_commands(MatchQueue& acciones){
    ActionCommand command({PlayerActionType::NONE, 0, 0}, &this->match_logic);
    while (acciones.pop_command(command)) {
        commands.push_back(command);
    }
}

void MatchState::execute_commands(){
    for (auto command : commands) {
        command.execute();
    }
    commands.clear();
}

void MatchState::send_results(){}

MatchState::~MatchState(){}
