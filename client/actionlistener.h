#ifndef GAME_ACTION_LISTENER_H
#define GAME_ACTION_LISTENER_H

#include "common/dtosgame.h"

// Clase que abstrae la interaccion para unirse/crear una lobby.
// Y la informacion necesaria.
class ActionListener {
public:
    virtual void doaction(const PlayerActionDTO& action) = 0;
    virtual void disconnect() = 0;
    virtual ~ActionListener() {}
};

#endif
