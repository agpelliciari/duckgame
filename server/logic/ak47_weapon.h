
#ifndef AK47_WEAPON_H
#define AK47_WEAPON_H

#include "weapon.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"

class AK47Weapon: public Weapon {

private:
    int ammo;
    int reload_time;
    int dispersion_index;

public:
    AK47Weapon();
    void get_weapon(TypeWeapon& type) override;
    void get_type(TypeDynamicObject &type) override;
    bool shoot(ShootingDirection direction, std::vector<PhysicalBullet> &bullets,
               Tuple bullet_position, PhysicalPlayer &player, bool &trigger) override;
    int get_ammo() override;
};


#endif //AK47_WEAPON_H
