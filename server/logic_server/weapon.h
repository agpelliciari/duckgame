

#ifndef WEAPON_H
#define WEAPON_H

#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "tuple.h"
#include "physical_bullet.h"

class Weapon {

public:
    virtual void get_weapon(TypeWeapon& type) = 0;
    virtual void shoot(ShootingDirection direction,
                       std::vector <PhysicalBullet> &bullets, Tuple bullet_position) = 0;
    virtual ~Weapon() = default;
};


#endif  // WEAPON_H
