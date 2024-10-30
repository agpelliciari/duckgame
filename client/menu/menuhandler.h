#ifndef LOBBY_MENU_MANAGER_H
#define LOBBY_MENU_MANAGER_H

#include "client/core/lobby_client_sender.h"
#include "common/dtos.h"

class MenuHandler {
private:
    LobbyClientSender sender;

public:
    explicit MenuHandler(LobbyClientSender&& _sender);

    void setHostnamePort(std::string hostaname, std::string port);

    void createSoloLobby();

    void createDuoLobby();

    void joinSoloLobby(int lobbyId);

    void joinDuoLobby(int lobbyId);

    void startLobby(std::string map);

    ~MenuHandler();

private:
    void createLobby(uint8_t playercount);

    void joinLobby(uint8_t playercount, unsigned int lobbyId);

};

#endif
