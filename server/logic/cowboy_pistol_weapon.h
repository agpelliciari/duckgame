
#ifndef COWBOY_PISTOL_WEAPON_H
#define COWBOY_PISTOL_WEAPON_H

#include "weapon.h"
#include "tuple.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"
#include "bullet.h"

class CowboyPistolWeapon: public Weapon{

    private:
        int ammo;
        int bullet_range;

    public:
        CowboyPistolWeapon();
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction,
                   std::vector<Bullet> &bullets, Tuple bullet_position, PhysicalPlayer &player,
                   bool &trigger, int id_player) override;
        int get_ammo() override;
};

#endif //COWBOY_PISTOL_WEAPON_H
