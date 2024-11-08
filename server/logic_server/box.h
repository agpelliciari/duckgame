

#ifndef BOX_H
#define BOX_H

#include "tuple.h"

class Box {

    private:
        Tuple spawn_point;
        Tuple dimension;
        bool spawned;


    public:

        Box(int spawn_x, int spawn_y);
        Tuple get_spawn_point();
        Tuple get_dimension();
        bool is_spawned();


};


#endif  // BOX_H
