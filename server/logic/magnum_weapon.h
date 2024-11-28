
#ifndef MAGNUM_WEAPON_H
#define MAGNUM_WEAPON_H

#include "weapon.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"

class MagnumWeapon: public Weapon {

    private:
        int ammo;
    public:
        MagnumWeapon();
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction,
                   std::vector<PhysicalBullet> &bullets, Tuple bullet_position, PhysicalPlayer &player) override;

};



#endif //MAGNUM_WEAPON_H
