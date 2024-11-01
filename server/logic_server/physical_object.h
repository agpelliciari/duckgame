
#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include "tuple.h"

class PhysicalObject {

    private:
        Tuple initial_position;
        Tuple actual_position;
        Tuple dimension;
        Tuple speed;
        int gravity;
        int time_step;

    public:

        PhysicalObject(int init_coord_x, int init_coord_y, int dimension_x,
                       int dimension_y, int speed_x, int speed_y, int gravity);

        void add_speed(int speed_x, int speed_y);
        bool check_collision(int coord_x, int coord_y);
        void move();
        void get_position(int &coord_x, int &coord_y);

};



#endif //PHYSICAL_OBJECT_H
