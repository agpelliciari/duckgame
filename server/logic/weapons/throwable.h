
#ifndef THROWABLE_H
#define THROWABLE_H

#include <vector>
#include "server/logic/physical/physical_grenade.h"
#include "common/dtosobject.h"
#include "bullet.h"
#include "server/logic/physical/match_map.h"
#include "server/logic/physical/tuple.h"


class Throwable {

    protected:
        int id_player;
        bool alive;
        TypeDynamicObject type;
        PhysicalGrenade physical_grenade;

    public:
        Throwable(int init_coord_x, int init_coord_y, TypeDynamicObject type, int id_player, bool is_banana);
        void move(const MatchMap& colition_map);

        void get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type);
        void get_pos(int &pos_x, int &pos_y);
        bool out_of_map();

        virtual void shoot_right() = 0;
        virtual void shoot_left() = 0;
        virtual void shoot_up() = 0;
        virtual bool exploded(std::vector<Bullet> &bullets, std::vector<MapPoint> &other_objects) = 0;

        virtual ~Throwable() = default;
};



#endif //THROWABLE_H
