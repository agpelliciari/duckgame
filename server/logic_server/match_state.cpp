
#include "./match_state.h"

#include <iostream>
#include <utility>

#include "common/clock.h"
MatchState::MatchState(): running(false), match_logic(), acciones(match_logic) {}

void MatchState::pushAction(const PlayerActionDTO& action) { acciones.push_command(action); }

void MatchState::playRound(MatchObserver& observer, MatchStatsInfo& stats) {
    stats.state = INICIADA;
    // start_players(observer);
    Clock clock(30);  // 16ms sleep == 60 frames por segundo aprox. 30 = 30 fps
    clock.resetnext();
    while (running && clock.tickcount() < 90) {
        //std::cout << "LOOP COUNT " << clock.tickcount()<< std::endl;
        this->step();
        this->send_results(observer);
        clock.tickNoRest();
    }
    std::cout << "FINISHED TICK COUNT OF 90!?" << clock.tickcount()<<std::endl;
    
    if(stats.numronda >= 5){ // Termino la partida!
        stats.state = TERMINADA;
        stats.champion_player = 1;
    } else{ // Termino la ronda o asi. Podria seguir internamente. O no.
        stats.state = PAUSADA; // Para probar.
        stats.numronda++;
        //stats.state = ROUND_END;  // Capaz a futuro para mandar las stats del round.
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
    match_logic.update_bullets();
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
    MatchDto dto;
    match_logic.get_dtos(dto.players, dto.objects);
    observer.updateState(dto);
}

void MatchState::add_objects(const struct ObjectsInfo& objects_info) {
    match_logic.add_boxes(objects_info.boxes);
    match_logic.add_items(objects_info.item_spawns);
}

MatchState::~MatchState() {}
