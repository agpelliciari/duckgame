#include "match_logic.h"

#include <iostream>


MatchLogic::MatchLogic(): colition_map(800, 640) {
    this->command_map[PlayerActionType::NONE] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };
    this->command_map[PlayerActionType::MOVE_LEFT] = [this](int index) {
        this->add_player_speed(index, -10, 0);
    };
    this->command_map[PlayerActionType::MOVE_LEFT_END] = [this](int index) {
        this->still_player(index);
    };

    this->command_map[PlayerActionType::MOVE_RIGHT] = [this](int index) {
        this->add_player_speed(index, 10, 0);
    };
    this->command_map[PlayerActionType::MOVE_RIGHT_END] = [this](int index) {
        this->still_player(index);
    };

    this->command_map[PlayerActionType::JUMP] = [this](int index) {
        this->player_jump_start(index);
    };

    this->command_map[PlayerActionType::FLAPPING_END] = [this](int index) {
        this->player_jump_end(index);
    };
    /*
    this->command_map[PlayerActionType::STAY_DOWN] = [this](int index) {
        this->add_player_speed(index, 0, 0);
    };*/
    this->command_map[PlayerActionType::STAY_DOWN_START] = [this](int index) {
        this->player_stay_down_start(index);
    };
    this->command_map[PlayerActionType::STAY_DOWN_END] = [this](int index) {
        this->player_stay_down_end(index);
    };

    this->command_map[PlayerActionType::FLAPPING_END] = [this](int index) {
        //this->add_player_speed(index, 0, 0);
    };

    this->command_map[PlayerActionType::AIM_UP_START] = [this](int index) {
        this->player_aim_up_start(index);
    };
    this->command_map[PlayerActionType::AIM_UP_END] = [this](int index) {
        this->player_aim_up_end(index);
    };
    this->command_map[PlayerActionType::SHOOT] = [this](int index) {
        this->player_shoot(index);
    };

    this->command_map[PlayerActionType::PICK_UP_ITEM] = [this](int index) {

        this->player_pick_up_item(index);
    };
    this->command_map[PlayerActionType::DROP_ITEM] = [this](int index) {

        this->player_drop_item(index);
    };
    // this->command_map[3] = [this](int index) { this->add_player_speed(index, 0, 0); };

}



void MatchLogic::add_player(int id, int spawn_point_index) {
    std::cout << "player SPAWN POINT INDEX: "<< spawn_point_index << std::endl;
    std::cout << "player SPAWN POINT pos: " << spawn_points[spawn_point_index].x*16
   <<", "<< spawn_points[spawn_point_index].y*16
   << std::endl;
    if (spawn_point_index < spawn_points.size()) {
        players.push_back(Player(id, spawn_points[spawn_point_index].x  * 16, spawn_points[spawn_point_index].y  * 16 + 1));
        std::cout << "spawn point x: " << spawn_points[spawn_point_index].x << ", y: " << spawn_points[spawn_point_index].y << std::endl;
    } else {
        players.push_back(Player(id, 10 + 50 * id, 1));
    }
    colition_map.add_collision(players.back().get_map_position(), players.back().get_dimension(),
                               CollisionTypeMap::PLAYER, players.back().get_id());
}

void MatchLogic::add_player_speed(int id, int speed_x, int speed_y) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.add_speed(speed_x, speed_y);
            return;
        }
    }
}

void MatchLogic::player_shoot(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.shoot(this->bullets);
            return;
        }
    }
}

void MatchLogic::player_jump_start(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.jump_start();
            return;
        }
    }
}

void MatchLogic::player_jump_end(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.jump_end();
            return;
        }
    }
}

void MatchLogic::player_pick_up_item(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.pick_up_item(this->spawn_places, this->dropped_items);
        }
    }
}

void MatchLogic::player_drop_item(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.drop_item(this->dropped_items);
        }
    }
}

void MatchLogic::player_aim_up_start(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.aim_up_start();
            return;
        }
    }
}

void MatchLogic::player_aim_up_end(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.aim_up_end();
            return;
        }
    }
}

void MatchLogic::player_stay_down_start(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.stay_down_start();
            return;
        }
    }
}

void MatchLogic::player_stay_down_end(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.stay_down_end();
            return;
        }
    }
}

void MatchLogic::still_player(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.still();
            return;
        }
    }
}

void MatchLogic::update_players(std::vector<int> &id_alive_players) {
    id_alive_players.clear();
    for (Player& player: players) {
        player.update(colition_map);
        if (player.is_still_alive()){
            id_alive_players.push_back(player.get_id());
        }
    }
}

void MatchLogic::update_colition_map() {
    colition_map.clear_map();
    for (Player& player: players) {
        colition_map.add_collision(player.get_map_position(), player.get_dimension(), CollisionTypeMap::PLAYER, player.get_id());
    }
    int box_index = 0;
    for (Box& box: boxes) {
        if (box.is_spawned()){
            colition_map.add_collision(box.get_spawn_point(), box.get_dimension(), CollisionTypeMap::BOX, box_index);
            box_index++;
        }
    }

    int block_index = 0;
    for (MapPoint& block: blocks) {
        Tuple position = {block.x, block.y};
        Tuple dimension = {16, 16};
        colition_map.add_collision(position, dimension, CollisionTypeMap::BLOCK, block_index);
        block_index ++;
    }

}

/*void MatchLogic::add_colition(PhysicalObject &object) {

    //colition_map.add_colition(object);

    //colition_map.add_temp_collision(position.x + dimension.x, position.y + dimension.y);

    // for (int i = 0; i < dimension.x; i++) {
    //     for (int j = 0; j < dimension.y; j++) {
    //     }
    // }
}*/

void MatchLogic::get_dtos(std::vector<PlayerDTO>& dtos,
                          std::vector<DynamicObjDTO>& objects, std::vector<SoundEventType>& sounds) {
    for (Player &player: players) {

        PlayerDTO dto;
        
        player.get_data(dto.id, dto.pos.x, dto.pos.y, dto.weapon, dto.helmet, dto.chest_armor,
                        dto.move_action, dto.doing_action, dto.is_alive, dto.aiming_up);
        player.get_sounds(sounds);
        dtos.push_back(dto);
    }

    for (Box box: boxes){
        if (box.is_spawned()){
            DynamicObjDTO dto = {0, 0, TypeDynamicObject::BOX};
            Tuple position = box.get_spawn_point();
            dto.pos.x = position.x;
            dto.pos.y = position.y;
            objects.push_back(dto);
        }
    }

    for (SpawnPlace &spawn_place: spawn_places) {
        if (spawn_place.is_spawned()){
            DynamicObjDTO dto = {0, 0, TypeDynamicObject::NONE};
            spawn_place.get_data(dto.pos.x, dto.pos.y, dto.type);
            objects.push_back(dto);
        }
    }

    for (DroppedItem &dropped_item: dropped_items) {
        if (dropped_item.is_alive()){
            DynamicObjDTO dto = {0, 0, TypeDynamicObject::NONE};
            dropped_item.get_data(dto.pos.x, dto.pos.y, dto.type);
            objects.push_back(dto);
        }
    }

    for (PhysicalBullet bullet: bullets) {
        DynamicObjDTO dto = {0, 0, TypeDynamicObject::PROJECTILE};
        bullet.get_map_info(dto.pos.x, dto.pos.y, dto.type);
        std::cout << "BULLET x: " << dto.pos.x << " y: " << dto.pos.y << std::endl;
        objects.push_back(dto);
    }

}

void MatchLogic::execute_move_command(int action_type, int index) {
    this->command_map[action_type](index);
}

void MatchLogic::add_boxes(const std::vector<struct MapPoint>& boxes){
    int id_box = 0;
    for (const struct MapPoint& box: boxes) {
        this->boxes.push_back(Box(id_box, box.x, box.y));
        id_box++;
    }
}

void MatchLogic::add_items(const std::vector<struct MapPoint>& items){
    for (const struct MapPoint& item: items) {
        this->spawn_places.push_back(SpawnPlace(item.x, item.y, 16, 16, 5, 0.025));
        spawn_places.back().spawn_item();
    }
}

void MatchLogic::add_blocks(const std::vector<struct MapPoint>& blocks){

    // MULTIPLICA POR EL SIZE!
    for (const struct MapPoint& block: blocks) {
        this->blocks.push_back(MapPoint(16*block.x, 16*block.y));
    }
}

void MatchLogic::add_spawn_points(const std::vector<struct MapPoint>& spawn_points){
    std::cout << "spawn points: " << spawn_points.size() << std::endl;

    for (const struct MapPoint& spawn_point: spawn_points) {
        this->spawn_points.push_back(MapPoint(spawn_point.x, spawn_point.y));

    }
}

void MatchLogic::add_item_spawns(const std::vector<struct MapPoint>& items_spawns){

    for (const struct MapPoint& spawn: items_spawns) {
        this->spawn_places.push_back(SpawnPlace(spawn.x * 16, spawn.y *16, 16, 5, 10, 1000/30));
        spawn_places.back().spawn_item();
    }
}

void MatchLogic::add_bullet(PhysicalBullet bullet){
    this->bullets.push_back(bullet);
}

void MatchLogic::damage_player(int id) {
    for (Player& player: players) {
        if (player.same_id(id)) {
            player.take_damage();
            return;
        }
    }
}

void MatchLogic::damage_box(int id) {
    for (Box& box: boxes) {
        if (box.same_id(id)) {
            box.take_damage();
            if (box.destroyed()){
                Tuple position = box.get_spawn_point();
                //this->spawn_places.push_back(SpawnPlace(position.x, position.y, 10, 10, 5, 0.025));
                //spawn_places.back().spawn_item();
            }
        }
    }
}

void MatchLogic::update_bullets(){
    for (auto bullet = bullets.begin(); bullet!=bullets.end();) {
        bool impacted = false;
        Collision collision(0, CollisionTypeMap::NONE);
        bullet->get_data(impacted, collision.type, collision.id);
        if (impacted) {
            if (collision.type == CollisionTypeMap::PLAYER) {
                this->damage_player(collision.id);
            }
            if (collision.type == CollisionTypeMap::BOX) {
                this->damage_box(collision.id);
            }
            std::cout << "ERASING BULLET !!\n";
            bullet = bullets.erase(bullet);
        } else {
            std::cout << "MOVING BULLET !!\n";
            bullet->move(colition_map);
            ++bullet;
        }
    }
}

void MatchLogic::update_dropped_items(){
    for (auto it = dropped_items.begin(); it!=dropped_items.end();) {
        if (!it->is_alive()){
            std::cout << "ERASING ITEM !!\n";
            it = dropped_items.erase(it);
        } else {
            it ++;
        }

    }
}

void MatchLogic::clear_players(){
    players.clear();
}

void MatchLogic::update_spawn_places(){
    for (SpawnPlace &spawn: this->spawn_places) {
        spawn.spawn_item();
    }
}

void MatchLogic::update_spawn_points(){
    for (SpawnPlace &spawn: this->spawn_places) {
        spawn.pass_time();
    }
}

void MatchLogic::clear_objects(){
    //spawn_points.clear();
    boxes.clear();
    //spawn_places.clear();
    dropped_items.clear();
    bullets.clear();
}

void MatchLogic::resize_map(const int width, const int height){
    colition_map.setSize(16*width, 16*height);
}

void MatchLogic::reset_map(){
    
    spawn_places.clear();
    spawn_points.clear();
    dropped_items.clear();
    boxes.clear();
    blocks.clear();
    bullets.clear();
    
    colition_map.clear_map();
}

MatchLogic::~MatchLogic() {}
