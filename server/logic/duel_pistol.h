
#ifndef DUEL_PISTOL_H
#define DUEL_PISTOL_H

#include "weapon.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"

class DuelPistol : public Weapon{

    private:
        int ammo;
    public:
        DuelPistol();
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        void shoot(ShootingDirection direction,
                   std::vector<PhysicalBullet> &bullets, Tuple bullet_position, PhysicalPlayer &player) override;

};



#endif //DUEL_PISTOL_H
