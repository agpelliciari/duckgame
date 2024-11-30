
#ifndef BANANA_WEAPON_H
#define BANANA_WEAPON_H

#include "weapon.h"
#include "tuple.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"
#include "bullet.h"
#include "common/gameevents.h"

class BananaWeapon : public Weapon{

    private:
        int ammo;

    public:
        BananaWeapon();
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction, std::vector<Bullet> &bullets,
                   Tuple bullet_position, PhysicalPlayer &player, bool &trigger,
                   int id_player, std::vector<SoundEventType> &player_sounds) override;
        int get_ammo() override;

};

#endif //BANANA_WEAPON_H
