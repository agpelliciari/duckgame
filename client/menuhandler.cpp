#include "menuhandler.h"

#include <utility>

MenuHandler::MenuHandler(LobbyClientSender&& _sender): sender(std::move(_sender)) {}

// Seguro se separe el player count a futuro !! en otro metodo setplayercount!
void MenuHandler::joinLobby(uint8_t playercount, unsigned int idlobby) {
    sender.joinLobby(playercount, idlobby);
}
void MenuHandler::createLobby(uint8_t playercount) { sender.createLobby(playercount); }

void MenuHandler::cancel() {
    sender.cancel();  // Seguro innecesario?! o bue depende
}

void MenuHandler::doaction(const lobby_action& action) {
    sender.doaction(action);  // Por ahora no hace mucho la vd.
}

MenuHandler::~MenuHandler() {}
