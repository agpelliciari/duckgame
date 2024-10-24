
#include "./match_state.h"
#include <utility>
#include <iostream>
MatchState::MatchState(): running(false), match_logic(), acciones(match_logic) {}

void MatchState::pushAction(const PlayerActionDTO& action) { acciones.push_command(action); }

void MatchState::loop(PlayerContainer& observer) {

    for (unsigned int i = 1; i <= observer.getPlayers()[0]; i++) {
        match_logic.add_player(i);
        std::cout << "New player added with id: "<< i << std::endl;
    }
    running = true;
    while (running) {
        this->receive_commands();
        //this->execute_commands();
        //this->send_results();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    observer.updateState(MatchDto(INICIADA, 1));
}

void MatchState::receive_commands() {
    ActionCommand command({PlayerActionType::NONE, 0, 0}, &this->match_logic);
    if (acciones.pop_command(command)) {
        command.execute();
    }
}

void MatchState::execute_commands() {
    for (auto command: commands) {
        command.execute();
    }
    commands.clear();
}

void MatchState::stop(){
    running = false;
}

void MatchState::send_results() {}

MatchState::~MatchState() {}
