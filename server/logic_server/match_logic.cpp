#include "match_logic.h"

#include <iostream>

MatchLogic::MatchLogic() {
    this->command_map[0] = [this](int index) { this->add_player_speed(index, 0, 0); };
    this->command_map[1] = [this](int index) { this->add_player_speed(index, -3, 0); };
    this->command_map[2] = [this](int index) { this->add_player_speed(index, 3, 0); };
    this->command_map[3] = [this](int index) { this->add_player_speed(index, 20, 0); };
    this->command_map[4] = [this](int index) { this->add_player_speed(index, -1, 0); };
}

void MatchLogic::add_player(int id) { players.push_back(Player(id, 0, 0)); }

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

void MatchLogic::update_player_positions() {
    for (Player& player: players) {
        player.update_position();
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

void MatchLogic::execute_move_command(int action_type, int index) {}

MatchLogic::~MatchLogic() {}
