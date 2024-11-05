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

    MenuAction(Action action, int lobbyId);

public:
    MenuAction();

    static MenuAction SetLobbyId(int lobbyId);

    static MenuAction AddSoloToLobby();

    static MenuAction AddDuoToLobby();

    static MenuAction RemovePlayerFromLobby();

    static MenuAction FailJoin();

    static MenuAction FailCreate();

    static MenuAction StartLobby();

    static MenuAction CancelLobby();

    void exec(Menu& menu);
};

#endif