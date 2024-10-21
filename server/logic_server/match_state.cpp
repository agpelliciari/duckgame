
#include "./match_state.h"

MatchState::MatchState(): running(false), match_logic(),acciones(match_logic) {}

void MatchState::pushAction(const PlayerActionDTO& action) { acciones.push_command(action); }

void MatchState::loop(PlayerContainer& observer) {
    running = true;
    while (running) {
        this->receive_commands(acciones);
        this->execute_commands();
        this->send_results();
    }
    observer.updateState(MatchDto(INICIADA, 1));
}

void MatchState::receive_commands(MatchQueue& acciones) {
    ActionCommand command({PlayerActionType::NONE, 0, 0}, &this->match_logic);
    while (acciones.pop_command(command)) {
        commands.push_back(command);
    }
}

void MatchState::execute_commands() {
    for (auto command: commands) {
        command.execute();
    }
    commands.clear();
}

void MatchState::send_results() {}

MatchState::~MatchState() {}
