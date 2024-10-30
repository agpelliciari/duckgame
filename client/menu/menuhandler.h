#ifndef LOBBY_MENU_MANAGER_H
#define LOBBY_MENU_MANAGER_H

#include <string>

#include "client/core/game_loop.h"
#include "client/core/lobby_client_sender.h"
#include "common/dtos.h"

class MenuHandler {
private:
    GameLoop& connector;
    // GameContext& context;
    LobbyClientSender sender;

public:
    explicit MenuHandler(GameLoop& _connector, GameContext& _context);

    void setHostnamePort(const std::string& hostaname, const std::string& port);

    void createSoloLobby();

    void createDuoLobby();

    void joinSoloLobby(int lobbyId);

    void joinDuoLobby(int lobbyId);

    void startLobby(const std::string& map);

    ~MenuHandler();
};

#endif
