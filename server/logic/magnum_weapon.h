
#ifndef MAGNUM_WEAPON_H
#define MAGNUM_WEAPON_H

#include "weapon.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"
#include "bullet.h"
#include "common/gameevents.h"
#include "grenade.h"

class MagnumWeapon: public Weapon {

    private:
        int ammo;
        int bullet_range;

    public:
        MagnumWeapon();
        
        SoundEventType shoot_sound() const override;        
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction, std::vector<Bullet> &bullets,
                   Tuple bullet_position, PhysicalPlayer &player, bool &trigger,
                   int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades) override;
        int get_ammo() override;
};



#endif //MAGNUM_WEAPON_H
