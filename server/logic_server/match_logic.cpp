
#include "match_logic.h"

MatchLogic::MatchLogic(){}

void MatchLogic::add_player(Player player){
    players.push_back(player);
}

void MatchLogic::move_player_left(int id){
    for (Player player :players){
        if (player.same_id(id)){
            player.move_left();
        }
    }
}

void MatchLogic::move_player_right(int id){
    for (Player player :players){
        if (player.same_id(id)){
            player.move_right();
        }
    }
}

void MatchLogic::move_player_jump(int id){
    for (Player player :players){
        if (player.same_id(id)){
            player.jump();
        }
    }
}

void MatchLogic::move_player_stay_down(int id){
    for (Player player :players){
        if (player.same_id(id)){
            player.stay_down();
        }
    }
}

void MatchLogic::get_dtos(std::vector <PlayerDTO> &dtos){
    for (Player player :players){
        PlayerDTO dto = {0, false, 0, 0, TypeWeapon::NONE, false, false, TypeMoveAction::NONE};
        player.get_data(dto.id, dto.coord_x, dto.coord_y, dto.weapon,
                        dto.helmet, dto.chest_armor, dto.move_action);
        dtos.push_back(dto);
    }
}

MatchLogic::~MatchLogic(){}

