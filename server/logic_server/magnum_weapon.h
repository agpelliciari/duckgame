
#ifndef MAGNUM_WEAPON_H
#define MAGNUM_WEAPON_H

#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"

class magnum_weapon: public Weapon {

    private:
        int ammo;
    public:
        MagnumWeapon();
    void get_weapon(TypeWeapon& type) override;
    void shoot(ShootingDirection direction,
                   std::vector<PhysicalBullet> &bullets, Tuple bullet_position) override;

};



#endif //MAGNUM_WEAPON_H
