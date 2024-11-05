#include "menuAction.h"

#include "menu.h"

MenuAction::MenuAction(Action action, int lobbyId): action(action), lobbyId(lobbyId) {}

MenuAction::MenuAction(): action(Action::None), lobbyId(-1) {}

MenuAction MenuAction::SetLobbyId(int lobbyId) { return MenuAction(Action::SetLobbyId, lobbyId); }

MenuAction MenuAction::AddSoloToLobby() { return MenuAction(Action::AddSoloToLobby, -1); }

MenuAction MenuAction::AddDuoToLobby() { return MenuAction(Action::AddDuoToLobby, -1); }

MenuAction MenuAction::RemovePlayerFromLobby() {
    return MenuAction(Action::RemovePlayerFromLobby, -1);
}

MenuAction MenuAction::FailJoin() { return MenuAction(Action::FailJoin, -1); }

MenuAction MenuAction::FailCreate() { return MenuAction(Action::FailCreate, -1); }

MenuAction MenuAction::StartLobby() { return MenuAction(Action::StartLobby, -1); }

MenuAction MenuAction::CancelLobby() { return MenuAction(Action::CancelLobby, -1); }

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
            menu.displayNotification("Error: Join Failed");
            break;
        case Action::FailCreate:
            menu.reset();
            menu.displayNotification("Error: Creation Failed");
            break;
        case Action::CancelLobby:
            menu.reset();
            menu.displayNotification("The Host closed the room");
            break;
        case Action::StartLobby:
            menu.startLobby();
            break;
        case Action::None:
            throw std::runtime_error("Exec on uninitialized menu action");
    }
}
