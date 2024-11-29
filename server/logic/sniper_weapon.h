

#ifndef SNIPER_WEAPON_H
#define SNIPER_WEAPON_H

#include "weapon.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"
#include "bullet.h"

class SniperWeapon : public Weapon{

    private:
        int ammo;
        int charging_time;
        int init_charging_time;
        int final_charging_time;
        bool charged;
        int bullet_range;

    public:
        SniperWeapon();
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction,
                   std::vector<Bullet> &bullets, Tuple bullet_position, PhysicalPlayer &player, bool &trigger, int id_player) override;
        void shoot_sniper(ShootingDirection direction,
                           std::vector<Bullet> &bullets,
                           Tuple bullet_position, int id_player);
        int get_ammo() override;


};



#endif //SNIPER_WEAPON_H
