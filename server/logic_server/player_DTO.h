
#include "type_move_action.h"
#include "type_weapon.h"


#ifndef PLAYER_DTO_H
#define PLAYER_DTO_H

struct PlayerDTO{
    int id;
    bool is_alive;
    int coord_x;
    int coord_y;
    TypeWeapon weapon;
    bool helmet;
    bool chest_armor;
    TypeMoveAction move_action;

    PlayerDTO(int id_, bool alive, int x, int y, TypeWeapon w, bool h, bool armor, TypeMoveAction action)
        : id(id_), is_alive(alive), coord_x(x), coord_y(y), weapon(w), helmet(h), chest_armor(armor), move_action(action) {}

};

#endif //PLAYER_DTO_H
