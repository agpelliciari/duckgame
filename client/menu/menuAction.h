#ifndef MENUACTION_H
#define MENUACTION_H

#include <cstdint>
#include <string>

class Menu;

enum Action {
    SetLobbyId,
    AddSoloToLobby,
    AddDuoToLobby,
    RemovePlayerFromLobby,
    FailJoin,
    FailCreate,
    StartLobby,
    CancelLobby,
    None
};

class MenuAction {
private:
    Action action;
    int lobbyId;
    std::string message;

    MenuAction(Action action, int lobbyId, const std::string& message);

public:
    MenuAction();

    static MenuAction SetLobbyId(int lobbyId);

    static MenuAction AddSoloToLobby();

    static MenuAction AddDuoToLobby();

    static MenuAction RemovePlayerFromLobby();

    static MenuAction FailJoin(const std::string& message);

    static MenuAction FailCreate(const std::string& message);

    static MenuAction StartLobby();

    static MenuAction CancelLobby(const std::string& message);

    void exec(Menu& menu);
};

#endif