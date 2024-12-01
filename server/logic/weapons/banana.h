
#ifndef BANANA_H
#define BANANA_H

#include <vector>
#include "server/logic/physical/physical_grenade.h"
#include "common/dtosobject.h"
#include "bullet.h"
#include "server/logic/physical/match_map.h"
#include "server/logic/physical/tuple.h"
#include "throwable.h"
#include <vector>
#include "server/logic/physical/map_object.h"
#include "server/logic/physical/tuple.h"
#include "server/logic/physical/collision.h"

class Banana : public Throwable{

    public:
        Banana(int init_coord_x, int init_coord_y, int id_player);
        void shoot_right() override;
        void shoot_left() override;
        void shoot_up() override;
        bool exploded(std::vector<Bullet> &bullets, std::vector<MapPoint> &other_objects) override;

};

#endif //BANANA_H
