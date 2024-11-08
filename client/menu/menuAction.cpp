#include "menuAction.h"

#include "menu.h"

MenuAction::MenuAction(Action action, int lobbyId, const std::string& message): action(action), lobbyId(lobbyId), message(message) {}

MenuAction::MenuAction(): action(Action::None), lobbyId(-1), message("") {}

MenuAction MenuAction::SetLobbyId(int lobbyId) { return MenuAction(Action::SetLobbyId, lobbyId, ""); }

MenuAction MenuAction::AddSoloToLobby() { return MenuAction(Action::AddSoloToLobby, -1, ""); }

MenuAction MenuAction::AddDuoToLobby() { return MenuAction(Action::AddDuoToLobby, -1, ""); }

MenuAction MenuAction::RemovePlayerFromLobby() {
    return MenuAction(Action::RemovePlayerFromLobby, -1, "");
}

MenuAction MenuAction::FailJoin(const std::string& message) { return MenuAction(Action::FailJoin, -1, message); }

MenuAction MenuAction::FailCreate(const std::string& message) { return MenuAction(Action::FailCreate, -1, message); }

MenuAction MenuAction::StartLobby() { return MenuAction(Action::StartLobby, -1, ""); }

MenuAction MenuAction::CancelLobby(const std::string& message) { return MenuAction(Action::CancelLobby, -1, message); }

void MenuAction::exec(Menu& menu) {
    switch (action) {
        case Action::SetLobbyId:
            menu.updateIdDisplayedInLobby(lobbyId);
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
