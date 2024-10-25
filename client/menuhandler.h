#ifndef LOBBY_MENU_MANAGER_H
#define LOBBY_MENU_MANAGER_H

#include "common/dtos.h"

// Clase que abstrae la interaccion para unirse/crear una lobby.
// Y la informacion necesaria.
class MenuHandler {
public:
    virtual void joinLobby(uint8_t playercount, unsigned int idlobby) = 0;
    virtual void createLobby(uint8_t playercount) = 0;
    virtual void cancel() = 0;
    virtual void doaction(const lobby_action& action) = 0;
    virtual ~MenuHandler() {}
};

#endif
