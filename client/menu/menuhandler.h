#ifndef LOBBY_MENU_MANAGER_H
#define LOBBY_MENU_MANAGER_H

#include <string>

#include "client/core/lobby_client_sender.h"
#include "client/core/lobby_connector.h"
#include "common/dtos.h"

class MenuHandler {
private:
    LobbyConnector& connector;  // cppcheck-suppress unusedStructMember
    LobbyClientSender* sender;  // cppcheck-suppress unusedStructMember

public:
    explicit MenuHandler(LobbyConnector& _connector);

    void setHostnamePort(const std::string& hostaname, const std::string& port);

    void createSoloLobby();

    void createDuoLobby();

    void joinSoloLobby(int lobbyId);

    void joinDuoLobby(int lobbyId);

    void startLobby(const std::string& map);

    ~MenuHandler();
};

#endif
