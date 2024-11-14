

#ifndef PHYSICAL_BULLET_H
#define PHYSICAL_BULLET_H

#include "physical_object.h"

class PhysicalBullet: public PhysicalObject{

    private:

        bool impacted;
        bool impacted_in_player;
        int id_impacted_player;

    public:
        PhysicalBullet(int init_coord_x, int init_coord_y);

        void react_to_sides_collision(bool is_player, int id_player) override;
        void react_to_down_collision(bool is_player, int id_player) override;
        void react_to_up_collision(bool is_player, int id_player) override;

        void shoot_right();
        void shoot_left();
        void shoot_up();

        void get_data(bool &impacted, bool &impacted_in_player, int &id_impacted_player);

};



#endif //PHYSICAL_BULLET_H
