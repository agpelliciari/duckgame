
#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "common/dtosplayer.h"
#include "tuple.h"

class PhysicalObject {

    private:
        Tuple initial_position;
        Tuple actual_position;
        Tuple dimension;
        Tuple speed;

        int gravity;
        float time_step;
        int flap_attemps;

    public:

        PhysicalObject(int init_coord_x, int init_coord_y, int dimension_x,
                       int dimension_y, int speed_x, int speed_y, int gravity);

        void add_speed(int speed_x, int speed_y);
        bool check_collision(int coord_x, int coord_y);
        void stop_moving_x();
        void stop_moving_y();
        void move();
        void update_action(TypeMoveAction& move_action);
        void get_position(int &coord_x, int &coord_y);

        //~PhysicalObject();
};



#endif //PHYSICAL_OBJECT_H
