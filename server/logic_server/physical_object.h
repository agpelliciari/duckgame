
#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "common/dtosplayer.h"
#include "tuple.h"
#include <vector>

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

        PhysicalObject(int init_coord_x, int init_coord_y, int dimension_x,
                       int dimension_y, int speed_x, int speed_y, int gravity);

        void add_speed(int speed_x, int speed_y);
        bool check_collision(int coord_x, int coord_y);
        void stop_moving_x();
        void stop_moving_y();
        void move(std::vector<std::vector<bool>> &colition_map);
        void update_action(TypeMoveAction& move_action);
        void get_position(int &coord_x, int &coord_y);
        bool check_collision(std::vector<std::vector<bool>> &colition_map);
        bool check_left_collision(std::vector<std::vector<bool>> &colition_map);
        bool check_right_collision(std::vector<std::vector<bool>> &colition_map);
        bool check_down_collision(std::vector<std::vector<bool>> &colition_map);
        bool check_up_collision(std::vector<std::vector<bool>> &colition_map);
        Tuple get_real_position();
        //~PhysicalObject();
};



#endif //PHYSICAL_OBJECT_H
