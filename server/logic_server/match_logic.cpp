#include "match_logic.h"

#include <iostream>

MatchLogic::MatchLogic(): game_map(std::vector<std::vector<bool>>(700, std::vector<bool>(500, false))),
                        colition_map(game_map){
    this -> build_map();
    this->command_map[0] = [this](int index) { this->add_player_speed(index, 0, 0); };
    this->command_map[1] = [this](int index) { this->add_player_speed(index, -10, 0); };
    this->command_map[2] = [this](int index) { this->add_player_speed(index, 10, 0); };
    this->command_map[3] = [this](int index) { this->add_player_speed(index, 0, 0); };
    this->command_map[4] = [this](int index) { this->add_player_speed(index, 0, 60); };
}

void MatchLogic::add_player(int id) { players.push_back(Player(id, 10 + id * 50, 50)); }

void MatchLogic::add_player_speed(int id, int speed_x, int speed_y) {
    for (Player& player : players) {
        if (player.same_id(id)){
            if (speed_x == 0 && speed_y == 0) {
                player.still();
            }
            else {
                player.add_speed(speed_x, speed_y);
            }
        }
    }
}

void MatchLogic::update_players() {
    for (Player& player: players) {
        player.update(colition_map);
    }
}

void MatchLogic::update_colition_map(){
    colition_map = game_map;
    for (Player& player : players) {
        Tuple position = player.get_position();
        Tuple dimension_player = {10, 30};
        add_colition(position, dimension_player);
    }

}

void MatchLogic::add_colition(Tuple position, Tuple dimension) {
    for (int i = 0; i < dimension.x; i++) {
        for (int j = 0; j < dimension.y; j++) {
            colition_map[position.y + j][position.x + i] = true;
        }
    }
}

void MatchLogic::get_dtos(std::vector<PlayerDTO>& dtos) {
    for (Player player: players) {

        PlayerDTO dto = {0, false, 0, 0, TypeWeapon::NONE, false, false, TypeMoveAction::NONE};
        player.get_data(dto.id, dto.coord_x, dto.coord_y, dto.weapon, dto.helmet, dto.chest_armor,
                        dto.move_action);

        dtos.push_back(dto);
    }
}

void MatchLogic::execute_move_command(int action_type, int index) {
    this->command_map[action_type](index);
}

void MatchLogic::build_map() {

    // defino un mapa vacio con paredes y pisos
    // tal que asi:
    //
    //    1 1 1 1 1 1 1 1 1 1
    //    1 0 0 0 0 0 0 0 0 1
    //    1 0 0 0 0 0 0 0 0 1
    //    1 0 0 0 0 0 0 0 0 1
    //    1 0 0 0 0 0 0 0 0 1
    //    1 1 1 1 1 1 1 1 1 1

    for (int i = 0; i < game_map[0].size() ; i++) {
        game_map[0][i] = true;
        game_map[game_map.size()-1][i] = true;

    }
    for (int i = 0; i < game_map.size() ; i++) {
        game_map[i][0] = true;
        game_map[i][game_map.size()-1] = true;
    }

}

MatchLogic::~MatchLogic() {}
