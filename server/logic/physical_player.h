
#ifndef PHYSICAL_PLAYER_H
#define PHYSICAL_PLAYER_H


#include "physical_object.h"
#include <vector>
#include "common/dtosplayer.h"
#include "match_map.h"
#include "tuple.h"
#include "shooting_direction.h"
#include "collision.h"
#include "type_collision.h"
#include "server/core/configuration.h"

class MatchMap;

enum PlayerMovingDir {
    NOT_SETTED = -3,
    NO_MOVE = 0,
    MOVING_LEFT = -1,
    MOVING_RIGHT = 1,
};

class PhysicalPlayer: public PhysicalObject {

    private:
        static constexpr int PLAYER_WIDTH = 10;
        static constexpr int PLAYER_HEIGHT = 22;
        static constexpr int FLAP_ATTEMPS = 10;

        Tuple initial_position;
        const Configuration& configs;
        int flap_attemps;
        PlayerMovingDir moving_dir;
        
        bool on_air;
        bool out_of_map;

    public:
        PhysicalPlayer(int init_coord_x, int init_coord_y, const Configuration& _configs);
        
        bool isOnAir() const;
        void react_to_sides_collision(Collision collision) override;
        void react_to_down_collision(Collision collision) override;
        void react_to_up_collision(Collision collision) override;
        void react_to_out_of_map() override;
        bool is_out_of_map();
        void stay_down_start();
        void stay_down_end();
        void jump_start();
        void jump_end();
        void update_action(TypeMoveAction& move_action);


        void check_moving_dir(const MatchMap& colition_map);
        
        void undo_moving(PlayerMovingDir mov_dir);        
        void change_moving(PlayerMovingDir new_dir);

        void stop_moving_x();

};

#endif  // PHYSICAL_PLAYER_H
