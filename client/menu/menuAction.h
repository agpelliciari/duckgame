#ifndef MENUACTION_H
#define MENUACTION_H

#include <cstdint>
#include <string>
#include <vector>

class Menu;

enum Action {
    SetLobbyId,
    SetLobbyMaps,
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
    std::vector<std::string> maps;
    std::string message;

    MenuAction(Action action, const std::string& message);

public:
    MenuAction();

    static MenuAction SetLobbyId(int lobbyId);

    static MenuAction SetLobbyMaps(const std::vector<std::string>& maps);

    static MenuAction AddSoloToLobby();

    static MenuAction AddDuoToLobby();

    static MenuAction RemovePlayerFromLobby();

    static MenuAction FailJoin(const std::string& message);

    static MenuAction FailCreate(const std::string& message);

    static MenuAction StartLobby();

    static MenuAction CancelLobby(const std::string& message);

    void exec(Menu& menu);

    void setId(int lobbyId);
    
    void setMaps(const std::vector<std::string>& maps);
};

#endif