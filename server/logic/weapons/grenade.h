
#ifndef GRENADE_H
#define GRENADE_H

#include <vector>
#include "server/logic/physical/physical_grenade.h"
#include "common/dtosobject.h"
#include "bullet.h"
#include "server/logic/physical/match_map.h"
#include "server/logic/physical/tuple.h"
#include "throwable.h"
#include "common/gameevents.h"

class Grenade : public Throwable{

    private:
        int detonation_time;
        int shoot_time;
        int id_player;
        bool alive;        
        PhysicalGrenade physical_grenade;
    public:
        Grenade(int init_coord_x, int init_coord_y, int id_player, int shoot_time);
        
        void get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type) override;
        void get_pos(int &pos_x, int &pos_y) override;
        
        void shoot_right() override;
        void shoot_left() override;
        void shoot_up() override;
        // Se mueve y verifica si debe hacer algo.
        // Retorna true si debe activarse/eliminarse.
        bool get_action(const MatchMap& colition_map, ThrowableAction& action) override;
        
        
        // En absoluto ideal. Pero para no refactorizar de mas....
        // Retorna el id a un objeto target i.e player para la banana a la que se aplica.
        int activate(std::vector<Bullet> &bullets, std::vector<GameEvent>& events) override;


};



#endif //GRENADE_H
