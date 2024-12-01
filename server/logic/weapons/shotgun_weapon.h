

#ifndef SHOTGUN_WEAPON_H
#define SHOTGUN_WEAPON_H

#include "weapon.h"
#include "common/dtosplayer.h"
#include "server/logic/weapons/shooting_direction.h"
#include "server/logic/physical/physical_bullet.h"
#include "server/logic/physical/physical_player.h"
#include "bullet.h"
#include "common/gameevents.h"
#include "grenade.h"

class ShotgunWeapon : public Weapon{

    private:
        int ammo;
        int charging_time;
        int init_charging_time;
        int final_charging_time;
        bool charged;
        int bullet_range;

    public:
        ShotgunWeapon(int base_ammo);
        
        SoundEventType shoot_sound() const override;                
        void get_weapon(TypeWeapon& type) override;
        void get_type(TypeDynamicObject &type) override;
        bool shoot(ShootingDirection direction,
                   std::vector<Bullet> &bullets, Tuple bullet_position, PhysicalPlayer &player,
                   bool &trigger, int id_player, std::vector<SoundEventType> &player_sounds, std::vector<Grenade> &grenades) override;
        void shoot_shotgun(ShootingDirection direction, std::vector <Bullet> &bullets,
                           Tuple bullet_position, int id_player, std::vector<SoundEventType> &player_sounds);
        int get_ammo() override;
        void cheat_ammo() override;

};

#endif //SHOTGUN_WEAPON_H
