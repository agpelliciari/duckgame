#include "common/dtosobject.h"
#include "tuple.h"


#ifndef ITEM_H
#define ITEM_H

class Item {

    private:
        TypeDynamicObject item;
        Tuple spawn_point;
        Tuple dimension;
        bool spawned;
        int time_respawn;
        float time_sleep;
        int timer;

    public:
        Item (TypeDynamicObject item, int position_x, int position_y,
             int range_x, int range_y, int time_respawn, float time_sleep);

        Tuple get_spawn_point();
        Tuple get_dimension();
        bool is_spawned();
        void pass_time();
        void take_item(TypeDynamicObject &item);
        void get_data(int &position_x_, int &position_y_, TypeDynamicObject &object_);
};



#endif //ITEM_H
