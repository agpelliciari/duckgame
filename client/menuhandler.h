#ifndef LOBBY_MENU_MANAGER_H
#define LOBBY_MENU_MANAGER_H

#include "client/core/lobby_client_sender.h"
#include "common/dtos.h"

// Clase que abstrae la interaccion para unirse/crear una lobby.
// Y la informacion necesaria.
class MenuHandler {
private:
    LobbyClientSender sender;  // cppcheck-suppress unusedStructMember
public:
    explicit MenuHandler(LobbyClientSender&& _sender);
    void joinLobby(uint8_t playercount, unsigned int idlobby);
    void createLobby(uint8_t playercount);
    void cancel();
    void doaction(const lobby_action& action);
    ~MenuHandler();
};

#endif
