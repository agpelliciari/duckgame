
#include "./match_state.h"

#include <iostream>
#include <utility>

#include "common/clock.h"
MatchState::MatchState(): running(false), match_logic(), acciones(match_logic) {}

void MatchState::pushAction(const PlayerActionDTO& action) { acciones.push_command(action); }

void MatchState::loop(MatchObserver& observer) {
    // start_players(observer);
    Clock clock(30);  // 16ms sleep == 60 frames por segundo aprox. 30 = 30 fps
    clock.resetnext();
    while (running) {
        this->step();
        this->send_results(observer);
        clock.tick();
    }
}


void MatchState::start_players(MatchObserver& observer) {

    std::vector<unsigned int> ids = observer.getPlayers();
    for (auto id = ids.begin(); id != ids.end();) {
        match_logic.add_player(*id);
        std::cout << "New player added with id: " << *id << std::endl;
        ++id;
    }

    running = true;
}

void MatchState::step() {
    this->receive_commands();
    this->execute_commands();
    match_logic.update_colition_map();
    match_logic.update_players();
}


void MatchState::receive_commands() {
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

void MatchState::stop() { running = false; }

void MatchState::send_results(MatchObserver& observer) {
    MatchDto dto = MatchDto(INICIADA, 1);
    match_logic.get_dtos(dto.players, dto.objects);
    observer.updateState(dto);
}

void MatchState::add_objects(const struct ObjectsInfo& objects_info) {
    match_logic.add_boxes(objects_info.boxes);
}

MatchState::~MatchState() {}
