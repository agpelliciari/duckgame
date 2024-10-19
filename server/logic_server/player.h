#include "coordinates.h"
#include "weapon.h"
#include "armor.h"
#include "action.h"
#include "player_types.h"

#ifndef PLAYER_H
#define PLAYER_H



class Player {

    private:
        int id;
        bool is_alive;
        Coordinates coordinates;
        Weapon weapon;
        Armor helmet;
        Armor chest_armor;
        Action move_action;

    public:

        Player(int id, int initial_x, int initial_y);

        bool same_id(int id);

        void get_data(int &id, int &x, int &y, TypeWeapon &weapon, bool &helmet_equipped,
                      bool &chest_armor_equipped, TypeMoveAction &move_action);

        void move_right();
        void move_left();
        void stay_down();
        void jump();

};



#endif //PLAYER_H
