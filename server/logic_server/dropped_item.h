
#ifndef DROPPED_ITEM_H
#define DROPPED_ITEM_H

#include <vector>
#include <memory>
#include "weapon.h"
#include "tuple.h"

class DroppedItem {

    private:

        bool alive;
        Tuple position;
        Tuple dimension;
        std::unique_ptr<Weapon> weapon;


};



#endif //DROPPED_ITEM_H
