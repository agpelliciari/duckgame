#ifndef LOBBY_MODE_H
#define LOBBY_MODE_H

#include "common/clientprotocol.h"

// Clase que abstrae la interaccion para unirse/crear una lobby.
// Y la informacion necesaria.
class LobbyMode {
public:
    virtual void exec(ClientProtocol& protocol) = 0;
    virtual ~LobbyMode() {}
};

#endif
