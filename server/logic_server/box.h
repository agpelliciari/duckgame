

#ifndef BOX_H
#define BOX_H

#include <vector>
#include "tuple.h"
#include "common/dtosplayer.h"
#include "common/dtosmap.h"
#include "common/dtosgame.h"
#include "common/dtosobject.h"
#include <cstdlib>
#include <ctime>

class Box {

    private:
        int id;
        Tuple spawn_point;
        Tuple dimension;
        bool spawned;
        int life_points;
        std::vector<TypeDynamicObject> possible_rewards;


    public:

        Box(int id, int spawn_x, int spawn_y);
        Tuple get_spawn_point();
        Tuple get_dimension();
        bool is_spawned();
        bool destroyed();
        void take_damage();
        bool same_id(int id);
        TypeDynamicObject get_item();


};


#endif  // BOX_H
