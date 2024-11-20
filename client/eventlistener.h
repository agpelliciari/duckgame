#ifndef GAME_EVENT_LISTENER_H
#define GAME_EVENT_LISTENER_H

#include "common/dtosgame.h"

// Clase que abstrae la interaccion para unirse/crear una lobby.
// Y la informacion necesaria.
class EventListener {
public:
    virtual void matchUpdated(const MatchDto& state) = 0;
    virtual void statsUpdated(const MatchStatsInfo& stats_update) = 0;
    // virtual void matchCanceled(const MatchDto& final_info) = 0;

    virtual ~EventListener() {}
};

#endif
