#include "menuAction.h"

#include "menu.h"

MenuAction::MenuAction(Action action, int lobbyId): action(action), lobbyId(lobbyId) {}

MenuAction::MenuAction(): action(Action::None), lobbyId(-1) {}

MenuAction MenuAction::SetLobbyId(int lobbyId) { return MenuAction(Action::SetLobbyId, lobbyId); }

MenuAction MenuAction::AddSoloToLobby() { return MenuAction(Action::AddSoloToLobby, -1); }

MenuAction MenuAction::AddDuoToLobby() { return MenuAction(Action::AddDuoToLobby, -1); }

MenuAction MenuAction::StartLobby() { return MenuAction(Action::StartLobby, -1); }

void MenuAction::exec(Menu& menu) {
    switch (action) {
        case Action::SetLobbyId:
            menu.updateIdDisplayedInLobby(lobbyId);
            break;
        case Action::AddSoloToLobby:
            menu.addPlayerToLobby(3);
            break;
        case Action::AddDuoToLobby:
            menu.addPlayerToLobby(3);
            menu.addPlayerToLobby(4);
            break;
        case Action::StartLobby:
            menu.startLobby();
            break;
        case Action::None:
            throw std::runtime_error("Exec on uninitialized menu action");
    }
}
