
#ifndef PHYSICAL_GRENADE_H
#define PHYSICAL_GRENADE_H

#include "server/logic/physical/physical_object.h"
#include "common/dtosobject.h"
#include "server/logic/physical/collision.h"
#include "type_collision.h"

class PhysicalGrenade : public PhysicalObject{

    private:
        bool impacted;
        Collision impacted_collision;


    public:
        PhysicalGrenade(int init_x, int init_y);

        void react_to_sides_collision(Collision collision) override;
        void react_to_down_collision(Collision collision) override;
        void react_to_up_collision(Collision collision) override;
        void react_to_out_of_map() override;

        void shoot_right();
        void shoot_left();
        void shoot_up();

        void impact_with_up_or_down_collision();

        void get_map_info(int &pos_x, int &pos_y);
        bool is_out_of_map();
        bool out_of_map;
};



#endif //PHYSICAL_GRENADE_H
