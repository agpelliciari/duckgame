#ifndef LOBBY_MENU_MANAGER_H
#define LOBBY_MENU_MANAGER_H

#include <string>

#include "client/core/lobby_client_sender.h"
#include "client/core/lobby_connector.h"
#include "common/dtos.h"
#include "common/queue.h"

#include "menuAction.h"

class MenuHandler {
private:
    LobbyConnector& connector;  // cppcheck-suppress unusedStructMember
    LobbyClientSender* sender;  // cppcheck-suppress unusedStructMember

    Queue<MenuAction> queueToMenu = Queue<MenuAction>(20);  // cppcheck-suppress unusedStructMember

public:
    explicit MenuHandler(LobbyConnector& _connector);

    void onSetHostnamePort(const std::string& hostaname, const std::string& port);

    void onCreateSoloLobby();

    void onCreateDuoLobby();

    void onJoinSoloLobby(int lobbyId);

    void onJoinDuoLobby(int lobbyId);

    void onStartLobby(const std::string& map);

    void setLobbyId(int lobbyId);

    void addSoloToLobby();

    void addDuoToLobby();

    void startLobby();

    ~MenuHandler();

private:
    bool tryPopActionToMenu(MenuAction& actionToMenu);
    friend class Menu;
};

#endif
