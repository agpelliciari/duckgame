

#ifndef PEWPEW_LASER_WEAPON_H
#define PEWPEW_LASER_WEAPON_H

#include "bullet.h"
#include "weapon.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"
#include "common/gameevents.h"
#include "grenade.h"

class PewPewLaserWeapon : public Weapon {

    private:
        int ammo;
        int bullet_range;

    public:
        PewPewLaserWeapon();
        SoundEventType shoot_sound() const override;                
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction, std::vector<Bullet> &bullets,
                   Tuple bullet_position, PhysicalPlayer &player, bool &trigger,
                   int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades) override;
        int get_ammo() override;
        void cheat_ammo() override;
};


#endif //PEWPEW_LASER_WEAPON_H
