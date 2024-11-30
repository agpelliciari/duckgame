
#ifndef GRENADE_H
#define GRENADE_H

#include <vector>
#include "physical_object.h"
#include "common/dtosobject.h"
#include "bullet.h"
#include "match_map.h"
#include "tuple.h"

class Grenade {

    private:
        int id_player;
        int detonation_time;
        bool alive;
        PhysicalGrenade physical_grenade;
        TypeDynamicObject type;
        int shoot_time;

    public:
        Grenade(int init_coord_x, int init_coord_y, TypeDynamicObject type, int id_player, int shoot_time);
        void move(const MatchMap& colition_map);
        void shoot_right();
        void shoot_left();
        void shoot_up();
        bool exploded(std::vector<Bullet> &bullets);
        void get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type);
        bool out_of_map();

};



#endif //GRENADE_H
