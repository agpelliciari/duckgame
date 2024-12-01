
#ifndef LASER_RIFLE_WEAPON_H
#define LASER_RIFLE_WEAPON_H

#include "weapon.h"
#include "server/logic/physical/tuple.h"
#include "common/dtosplayer.h"
#include "server/logic/weapons/shooting_direction.h"
#include "server/logic/physical/physical_bullet.h"
#include "server/logic/physical/physical_player.h"
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
        LaserRifleWeapon(int base_ammo);
        
        SoundEventType shoot_sound() const override;        
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction, std::vector<Bullet> &bullets,
                   Tuple bullet_position, PhysicalPlayer &player, bool &trigger,
                   int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades) override;
        int get_ammo() override;
        void cheat_ammo() override;

};



#endif //LASER_RIFLE_WEAPON_H
