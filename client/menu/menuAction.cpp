#include "menuAction.h"

#include "menu.h"

MenuAction::MenuAction(Action action, const std::string& message): action(action), message(message) {}

MenuAction::MenuAction(): action(Action::None), message("") {}

MenuAction MenuAction::SetLobbyId(int lobbyId) {
    MenuAction action = MenuAction(Action::SetLobbyId, "");
    action.setId(lobbyId);
    return action;
}

MenuAction MenuAction::SetLobbyMaps(const std::vector<std::string>& maps) {
    MenuAction action = MenuAction(Action::SetLobbyMaps, "");
    action.setMaps(maps);
    return action;
}

MenuAction MenuAction::AddSoloToLobby() { return MenuAction(Action::AddSoloToLobby, ""); }

MenuAction MenuAction::AddDuoToLobby() { return MenuAction(Action::AddDuoToLobby, ""); }

MenuAction MenuAction::RemovePlayerFromLobby() {
    return MenuAction(Action::RemovePlayerFromLobby, "");
}

MenuAction MenuAction::FailJoin(const std::string& message) { return MenuAction(Action::FailJoin, message); }

MenuAction MenuAction::FailCreate(const std::string& message) { return MenuAction(Action::FailCreate, message); }

MenuAction MenuAction::StartLobby() { return MenuAction(Action::StartLobby, ""); }

MenuAction MenuAction::CancelLobby(const std::string& message) { return MenuAction(Action::CancelLobby, message); }

void MenuAction::exec(Menu& menu) {
    switch (action) {
        case Action::SetLobbyId:
            menu.updateIdDisplayedInLobby(lobbyId);
            break;
        case Action::SetLobbyMaps:
            menu.updateMapsDisplayedInLobby(maps);
            break;
        case Action::AddSoloToLobby:
            menu.addPlayerToLobby();
            break;
        case Action::AddDuoToLobby:
            menu.addPlayerToLobby();
            menu.addPlayerToLobby();
            break;
        case Action::RemovePlayerFromLobby:
            menu.removePlayerFromLobby();
            break;
        case Action::FailJoin:
            menu.reset();
            menu.displayNotification(message);
            break;
        case Action::FailCreate:
            menu.reset();
            menu.displayNotification(message);
            break;
        case Action::CancelLobby:
            menu.reset();
            menu.displayNotification(message);
            break;
        case Action::StartLobby:
            menu.startLobby();
            break;
        case Action::None:
            throw std::runtime_error("Exec on uninitialized menu action");
    }
}

void MenuAction::setId(int newLobbyId) {
    lobbyId = newLobbyId;
}
    
void MenuAction::setMaps(const std::vector<std::string>& newMaps) {
    maps = newMaps;
}
