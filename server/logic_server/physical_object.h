
#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <vector>

#include "common/dtosplayer.h"
#include "match_map.h"
#include "tuple.h"

class MatchMap;

class PhysicalObject {

private:
    Tuple initial_position;
    Tuple actual_position;
    Tuple dimension;
    Tuple speed;

    int gravity;
    float time_step;
    int flap_attemps;
    bool on_air;

public:
    PhysicalObject(int init_coord_x, int init_coord_y, int dimension_x, int dimension_y,
                   int speed_x, int speed_y, int gravity);

    void add_speed(int speed_x, int speed_y);
    bool check_collision(int coord_x, int coord_y);
    void stop_moving_x();
    void stop_moving_y();
    void move(const MatchMap& colition_map);
    void update_action(TypeMoveAction& move_action);
    void get_position(int& coord_x, int& coord_y);
    bool check_collision();
    bool check_left_collision(const MatchMap& colition_map);
    bool check_right_collision(const MatchMap& colition_map);
    bool check_down_collision(const MatchMap& colition_map);
    bool check_up_collision(const MatchMap& colition_map);
    //bool detect_others_collision(int coord_x, int coord_y);
    Tuple get_position();
    Tuple get_dimension();
    Tuple get_real_position();
    //~PhysicalObject();
};


#endif  // PHYSICAL_OBJECT_H
