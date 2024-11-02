#ifndef LOBBY_MENU_MANAGER_H
#define LOBBY_MENU_MANAGER_H

#include <string>

#include "client/core/lobby_client_sender.h"
#include "client/core/lobby_connector.h"
#include "client/core/lobby_listener.h"
#include "common/dtos.h"
#include "common/queue.h"

#include "menuAction.h"

class MenuHandler: public LobbyListener {
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


    ~MenuHandler();

    // Acciones en el menu a partir de las notificaciones
    void setLobbyId(int lobbyId);
    void addSoloToLobby();
    void addDuoToLobby();
    void playerLeft();

    // Para recibir notificaciones de la lobby... son directos.
    void startedLobby() override;
    void canceledLobby() override;
    void failedJoin() override;
    void failedCreate() override;


    // Notificacion inicial sobre si se pudo crear/unirse a una lobby.
    void createdLobbyDual(const GameContext& context) override;
    void createdLobbySolo(const GameContext& context) override;

    void joinedLobbyDual(const GameContext& context) override;
    void joinedLobbySolo(const GameContext& context) override;

    void notifyInfo(GameContext& context, const lobby_info& info) override;

private:
    bool tryPopActionToMenu(MenuAction& actionToMenu);
    friend class Menu;
};

#endif
