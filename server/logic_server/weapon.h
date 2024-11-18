

#ifndef WEAPON_H
#define WEAPON_H

#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "tuple.h"
#include "physical_bullet.h"
#include "physical_player.h"

class Weapon {

public:
    virtual void get_weapon(TypeWeapon& type) = 0;
    virtual void shoot(ShootingDirection direction,
                       std::vector <PhysicalBullet> &bullets, Tuple bullet_position, PhysicalPlayer &player) = 0;
    virtual ~Weapon() = default;
};


#endif  // WEAPON_H
