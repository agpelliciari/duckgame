
#include "./match_state.h"

#include <iostream>
#include <utility>

#include "common/clock.h"


MatchState::MatchState(const Configuration& _configs): running(false), match_logic(_configs), acciones(match_logic), max_rounds(_configs.rounds_per_set), configs(_configs) {}

void MatchState::pushAction(const PlayerActionDTO& action) { acciones.push_command(action); }

void MatchState::playRound(MatchObserver& observer, MatchStatsInfo& stats) {
    stats.state = INICIADA;
    
    Clock clock(configs.frame_delay);  // 16ms sleep == 60 frames por segundo aprox. 30 = 30 fps
    clock.resetnext();

    while ((running /*&& clock.tickcount() < FPS * 2*/) && id_alive_players.size() > 1) {
        //std::cout << "LOOP COUNT " << clock.tickcount()<< std::endl;
        this->step();
        this->send_results(observer);
        clock.tickNoRest();

    }

    this->calculate_game_results(stats, id_alive_players[0]);
}

void MatchState::reset_map(const struct ObjectsInfo& info){
    
    match_logic.reset_map();
    match_logic.clear_objects();
    add_objects(info);
}

void MatchState::reset_objects(const struct ObjectsInfo& objects_info){
    match_logic.clear_objects();
    match_logic.add_boxes(objects_info.boxes);
    match_logic.update_spawn_places();
    //match_logic.add_items(objects_info.item_spawns);
}



void MatchState::add_objects(const struct ObjectsInfo& objects_info) {
    match_logic.resize_map(objects_info.map_width,objects_info.map_height);
    
    match_logic.add_spawn_points(objects_info.player_spawns);
    match_logic.add_blocks(objects_info.blocks);
    match_logic.add_boxes(objects_info.boxes);
    match_logic.add_item_spawns(objects_info.item_spawns);
}


void MatchState::start_players(MatchObserver& observer, MatchStatsInfo& stats) {

    stats.stats.clear();
    id_alive_players.clear();
    std::vector<unsigned int> ids = observer.getPlayers();

    int spawn_point_index = 0;
    for (auto id = ids.begin(); id != ids.end();) {
        stats.stats.push_back(PlayerStatDto(*id, 0));
        id_alive_players.push_back(*id);
        match_logic.add_player(*id, spawn_point_index);
        std::cout << "New player added with id: " << *id << "ind is " << spawn_point_index<< std::endl;
        ++id;
        spawn_point_index ++;
    }

    running = true;
}
void MatchState::reset_players(MatchObserver& observer){
    match_logic.clear_players();
    id_alive_players.clear();
    std::vector<unsigned int> ids = observer.getPlayers();
    int spawn_point_index = 0;
    
    for (auto id = ids.begin(); id != ids.end();) {
        id_alive_players.push_back(*id);
        match_logic.add_player(*id, spawn_point_index);
        std::cout << "Reset player added with id: " << *id << "ind is " << spawn_point_index<< std::endl;
        ++id;
        spawn_point_index++;
    }

}


void MatchState::calculate_game_results(MatchStatsInfo& stats, int actual_winner){
    int wins_curr = stats.addPlayerWin(actual_winner);
    //stats.stats.clear();
    //if(wins_curr < 0){ // No encontro el id!
    //}
    
    if (stats.numronda >= max_rounds){
        int id_champion = 0;
        if (only_one_winner(stats, id_champion)){
            stats.state = TERMINADA;
            stats.champion_player = id_champion;
        } else {
            stats.state = PAUSADA;
            stats.champion_player = actual_winner;
            max_rounds += configs.rounds_per_set;
        }
    } else {
        stats.state = ROUND_END;
        stats.champion_player = actual_winner;
    }
}

bool MatchState::only_one_winner(MatchStatsInfo& stats, int &id_champion){

    bool only_one_winner = false;
    
    // Almenos alguien debe tener esta cantidad sino siempre es false!
    int maximum_number_of_wins = configs.wins_needed-1; // -1 para que si es == lo ponga de ganador.  
    
    int id_champion_player = -1;
    for (const PlayerStatDto& player : stats.stats ) {
        if (player.wins > maximum_number_of_wins){
            only_one_winner = true;
            maximum_number_of_wins = player.wins;
            id_champion_player = player.id;
        } else if (player.wins == maximum_number_of_wins){
            only_one_winner = false;
            id_champion_player = -1;
        }
    }
    
    id_champion = id_champion_player;
    return only_one_winner;
}


void MatchState::step() {
    std::vector<ActionCommand> curr_commands = acciones.pop_commands();
    for (ActionCommand& command: curr_commands) {
        command.execute();
    }

    match_logic.update_colition_map();
    match_logic.update_players(this->id_alive_players);
    match_logic.update_bullets();
    match_logic.update_grenades();
    match_logic.update_dropped_items();
    match_logic.update_spawn_points();
}


void MatchState::receive_commands() {
    ActionCommand command(PlayerActionDTO(NONE, 0), &this->match_logic);
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
    match_logic.get_dtos(dto.players, dto.objects, dto.sounds);
    observer.updateState(dto);
}

MatchState::~MatchState() {}
