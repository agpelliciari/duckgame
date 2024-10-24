#include "match_logic.h"

#include <iostream>

MatchLogic::MatchLogic() {}

void MatchLogic::add_player(int id) { players.push_back(Player(id, 0, 0)); }

void MatchLogic::still_player(int id) {

    for (Player player: players) {
        if (player.same_id(id)) {
            player.still();
        }
    }
    std::cout << "player " << id << " is still" << std::endl;
}

void MatchLogic::move_player_left(int id) {

    for (Player& player: players) {
        if (player.same_id(id)) {
            player.move_left();
        }
    }
    std::cout << "player " << id << " moved left" << std::endl;
}

void MatchLogic::move_player_right(int id) {

    for (Player player: players) {
        if (player.same_id(id)) {
            player.move_right();
        }
    }
    std::cout << "player " << id << " moved right" << std::endl;
}

void MatchLogic::move_player_jump(int id) {

    for (Player player: players) {
        if (player.same_id(id)) {
            player.jump();
        }
    }
    std::cout << "player " << id << " jumped" << std::endl;
}

void MatchLogic::move_player_stay_down(int id) {

    for (Player player: players) {
        if (player.same_id(id)) {
            player.stay_down();
        }
    }
    std::cout << "player " << id << " stay down" << std::endl;
}

void MatchLogic::get_dtos(std::vector<PlayerDTO>& dtos) {
    for (Player player: players) {
        PlayerDTO dto = {0, false, 0, 0, TypeWeapon::NONE, false, false, TypeMoveAction::NONE};
        player.get_data(dto.id, dto.coord_x, dto.coord_y, dto.weapon, dto.helmet, dto.chest_armor,
                        dto.move_action);
        dtos.push_back(dto);
    }
}

MatchLogic::~MatchLogic() {}
