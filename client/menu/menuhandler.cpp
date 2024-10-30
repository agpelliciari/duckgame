#include "menuhandler.h"

#include <utility>


MenuHandler::MenuHandler(LobbyConnector& _connector): connector(_connector), sender(NULL) {}

void MenuHandler::setHostnamePort(const std::string& hostname, const std::string& port) {
    connector.setHostnamePort(hostname, port);
}

// Se hace el update del protocol en el sender cada vez se haga un llamado.
// Por si algo fallo.
void MenuHandler::createSoloLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y va a jugar 1 jugador"
              << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyCreator();
    sender->createLobby(false);
}

void MenuHandler::createDuoLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y van a jugar 2 jugadores"
              << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyCreator();

    sender->createLobby(true);
}

void MenuHandler::joinSoloLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y va a jugar 1 jugador" << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyJoin(lobbyId);
    sender->joinLobby(false, lobbyId);
}

void MenuHandler::joinDuoLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y van a jugar 2 jugadores" << std::endl;
    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyJoin(lobbyId);
    sender->joinLobby(true, lobbyId);
}

void MenuHandler::startLobby(const std::string& map) {
    std::cout << "Empeza con el mapa: " << map << std::endl;
    sender->notifyStart();
}

MenuHandler::~MenuHandler() {}
