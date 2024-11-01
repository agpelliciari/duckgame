#include "menuhandler.h"

#include <utility>

MenuHandler::MenuHandler(LobbyConnector& _connector): connector(_connector), sender(NULL) {}

void MenuHandler::onSetHostnamePort(const std::string& hostname, const std::string& port) {
    connector.setHostnamePort(hostname, port);
}

// Se hace el update del protocol en el sender cada vez se haga un llamado.
// Por si algo fallo.
void MenuHandler::onCreateSoloLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y va a jugar 1 jugador"
              << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyCreator();
    sender->createLobby(false);
    setLobbyId(9999);  // TODO: agregar el lobby id desde el protocolo
}

void MenuHandler::onCreateDuoLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y van a jugar 2 jugadores"
              << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyCreator();

    sender->createLobby(true);
    setLobbyId(9999);  // TODO: agregar el lobby id desde el protocolo
}

void MenuHandler::onJoinSoloLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y va a jugar 1 jugador" << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyJoin(lobbyId);
    sender->joinLobby(false, lobbyId);
    setLobbyId(lobbyId);
    // TODO: Llamar a addSoloToLobby o addDuoToLobby
    // dependiendo de si en el lobby el host es de 1 o 2
}

void MenuHandler::onJoinDuoLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y van a jugar 2 jugadores" << std::endl;
    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyJoin(lobbyId);
    sender->joinLobby(true, lobbyId);
    setLobbyId(lobbyId);
    // TODO: Llamar a addSoloToLobby o addDuoToLobby
    // dependiendo de si en el lobby el host es de 1 o 2
}

void MenuHandler::onStartLobby(const std::string& map) {
    std::cout << "Empeza con el mapa: " << map << std::endl;
    sender->notifyStart();
}

void MenuHandler::setLobbyId(int lobbyId) { queueToMenu.push(MenuAction::SetLobbyId(lobbyId)); }

void MenuHandler::addSoloToLobby() { queueToMenu.push(MenuAction::AddSoloToLobby()); }

void MenuHandler::addDuoToLobby() { queueToMenu.push(MenuAction::AddDuoToLobby()); }

void MenuHandler::startLobby() {  // TODO Llamar cuando el protocolo dice que empezo la partida
    queueToMenu.push(MenuAction::StartLobby());
}

bool MenuHandler::tryPopActionToMenu(MenuAction& actionToMenu) {
    return queueToMenu.try_pop(actionToMenu);
}

MenuHandler::~MenuHandler() {}
