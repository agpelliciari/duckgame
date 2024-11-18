
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

class MatchMap;

class PhysicalPlayer: public PhysicalObject {

    private:
        static constexpr int PLAYER_WIDTH = 16;
        static constexpr int PLAYER_HEIGHT = 22;
        static constexpr int FLAP_ATTEMPS = 10;

        Tuple initial_position;
        int flap_attemps;
        bool on_air;

    public:
        PhysicalPlayer(int init_coord_x, int init_coord_y);

        void react_to_sides_collision(Collision collision) override;
        void react_to_down_collision(Collision collision) override;
        void react_to_up_collision(Collision collision) override;
        void stay_down_start();
        void stay_down_end();
        void update_action(TypeMoveAction& move_action);
        void stop_moving_x();

};

#endif  // PHYSICAL_PLAYER_H
