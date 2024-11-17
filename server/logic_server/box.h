

#ifndef BOX_H
#define BOX_H

#include "tuple.h"

class Box {

    private:
        Tuple spawn_point;
        Tuple dimension;
        bool spawned;


    public:
        static constexpr int BOX_SIZE = 16;

        Box(int spawn_column, int spawn_row);
        Tuple get_spawn_point();
        Tuple get_dimension();
        bool is_spawned();


};


#endif  // BOX_H
