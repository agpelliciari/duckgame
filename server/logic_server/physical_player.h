
#ifndef PHYSICAL_PLAYER_H
#define PHYSICAL_PLAYER_H


#include "physical_object.h"
#include <vector>
#include "common/dtosplayer.h"
#include "match_map.h"
#include "tuple.h"

class MatchMap;

class PhysicalPlayer: public PhysicalObject {

    private:
        Tuple initial_position;
        int flap_attemps;
        bool on_air;

    public:
        PhysicalPlayer(int init_coord_x, int init_coord_y);

        void react_to_sides_collision();
        void react_to_down_collision();
        void react_to_up_collision();
        void update_action(TypeMoveAction& move_action);
        void stop_moving_x();

};

#endif  // PHYSICAL_PLAYER_H
