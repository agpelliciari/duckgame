
#ifndef THROWABLE_H
#define THROWABLE_H

#include <vector>
#include "common/dtosobject.h"
#include "common/gameevents.h"

#include "bullet.h"
#include "server/logic/physical/match_map.h"
#include "server/logic/physical/tuple.h"


enum ThrowableAction{
    ERASE_SELF,
    EXPLODE_SELF,
    SLIP_PLAYER
};

class Throwable {
    public:
        virtual void get_map_info(int &pos_x, int &pos_y, TypeDynamicObject &type) = 0;
        virtual void get_pos(int &pos_x, int &pos_y) =0;

        virtual void shoot_right() = 0;
        virtual void shoot_left() = 0;
        virtual void shoot_up() = 0;
        
        // Se mueve y verifica si debe hacer algo.
        // Retorna true si debe activarse/eliminarse.
        virtual bool get_action(const MatchMap& colition_map, ThrowableAction& action) = 0;
        
        
        // En absoluto ideal. Pero para no refactorizar de mas....
        // Retorna el id a un objeto target i.e player para la banana a la que se aplica.
        virtual int activate(std::vector<Bullet> &bullets, std::vector<GameEvent>& events) = 0;

        virtual ~Throwable() = default;
};



#endif //THROWABLE_H
