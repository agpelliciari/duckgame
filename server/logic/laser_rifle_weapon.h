
#ifndef LASER_RIFLE_WEAPON_H
#define LASER_RIFLE_WEAPON_H

#include "weapon.h"
#include "tuple.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"
#include "bullet.h"
#include "common/gameevents.h"
#include "grenade.h"


class LaserRifleWeapon : public Weapon{

    private:
        int ammo;
        int reload_time;
        int bullet_range;
        float dispersion_factor;
        int last_shoot_time;

    public:
        LaserRifleWeapon();
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction, std::vector<Bullet> &bullets,
                   Tuple bullet_position, PhysicalPlayer &player, bool &trigger,
                   int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades) override;
        int get_ammo() override;

};



#endif //LASER_RIFLE_WEAPON_H
