#include "common/dtosplayer.h"

#ifndef WEAPON_H
#define WEAPON_H


class Weapon {

private:
    TypeWeapon type;

public:
    Weapon();
    void get_weapon(const TypeWeapon& type);
};


#endif  // WEAPON_H
