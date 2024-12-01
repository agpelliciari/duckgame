
#ifndef GRENADE_WEAPON_H
#define GRENADE_WEAPON_H

#include "weapon.h"
#include "common/dtosplayer.h"
#include "shooting_direction.h"
#include "physical_bullet.h"
#include "physical_player.h"
#include "bullet.h"
#include "common/gameevents.h"
#include "grenade.h"

class GrenadeWeapon : public Weapon{

    private:
        int ammo;
    public:
        GrenadeWeapon();
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        
        SoundEventType shoot_sound() const override;

        bool shoot(ShootingDirection direction,
                   std::vector<Bullet> &bullets, Tuple bullet_position, PhysicalPlayer &player,
                   bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades) override;
        void shoot_shotgun(ShootingDirection direction, std::vector <Bullet> &bullets,
                           Tuple bullet_position, int id_player, std::vector<SoundEventType> &player_sounds);
        int get_ammo() override;
        void cheat_ammo() override;


};



#endif //GRENADE_WEAPON_H
