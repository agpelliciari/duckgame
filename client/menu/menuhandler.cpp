#include "menuhandler.h"

#include <utility>

static const char DEFAULT_HOST[] = "127.0.0.1";
static const char DEFAULT_PORT[] = "2048";


MenuHandler::MenuHandler(GameLoop& _connector, GameContext& _context):
        connector(_connector), sender(NULL, _context) {}

void MenuHandler::setHostnamePort(const std::string& hostname, const std::string& port) {
    connector.setHostnamePort(hostname.length() == 0 ? DEFAULT_HOST : hostname.c_str(),
                              port.length() == 0 ? DEFAULT_PORT : port.c_str());

    connector.updateLobbySender(sender);
}

void MenuHandler::createSoloLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y va a jugar 1 jugador"
              << std::endl;

    sender.createLobby(false);
}

void MenuHandler::createDuoLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y van a jugar 2 jugadores"
              << std::endl;

    sender.createLobby(true);
}

void MenuHandler::joinSoloLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y va a jugar 1 jugador" << std::endl;
    sender.joinLobby(false, lobbyId);
}

void MenuHandler::joinDuoLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y van a jugar 2 jugadores" << std::endl;
    sender.joinLobby(true, lobbyId);
}

void MenuHandler::startLobby(const std::string& map) {
    std::cout << "Empeza con el mapa: " << map << std::endl;
    sender.notifyStart();
}

MenuHandler::~MenuHandler() {}
