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
    sender = connector.setLobbyCreator(*this, false);
}

void MenuHandler::onCreateDuoLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y van a jugar 2 jugadores"
              << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyCreator(*this, true);
}

void MenuHandler::onJoinSoloLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y va a jugar 1 jugador" << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    connector.setLobbyJoin(*this, false, lobbyId);
    sender = NULL;  // El que joinea no manda cosas?
    // setLobbyId(lobbyId);
    //  TODO: Llamar a addSoloToLobby o addDuoToLobby
    //  dependiendo de si en el lobby el host es de 1 o 2
}

void MenuHandler::onJoinDuoLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y van a jugar 2 jugadores" << std::endl;
    connector.reset();  // Reset protocol and curr state si existe.
    connector.setLobbyJoin(*this, true, lobbyId);
    sender = NULL;
    // setLobbyId(lobbyId);
    //  TODO: Llamar a addSoloToLobby o addDuoToLobby
    //  dependiendo de si en el lobby el host es de 1 o 2
}

void MenuHandler::onStartLobby(const std::string& map) {
    std::cout << "Empeza con el mapa: " << map << std::endl;
    sender->notifyStart();
}


bool MenuHandler::tryPopActionToMenu(MenuAction& actionToMenu) {
    return queueToMenu.try_pop(actionToMenu);
}

MenuHandler::~MenuHandler() {}


// Acciones a menu...
void MenuHandler::setLobbyId(int lobbyId) { queueToMenu.push(MenuAction::SetLobbyId(lobbyId)); }

void MenuHandler::addSoloToLobby() { queueToMenu.push(MenuAction::AddSoloToLobby()); }

void MenuHandler::addDuoToLobby() { queueToMenu.push(MenuAction::AddDuoToLobby()); }

void MenuHandler::playerLeft() {}

// Acciones a menu.. Llamados/notificaciones directas ...
// Se podria pasar el codigo de error si se quiere mostrar un mensaje personalizado.
void MenuHandler::canceledLobby() { std::cerr << "menuhandler canceled lobby!" << std::endl; }
void MenuHandler::failedJoin() { std::cerr << "menuhandler failed join to lobby" << std::endl; }

void MenuHandler::failedCreate() { std::cerr << "menuhandler failed create lobby" << std::endl; }

void MenuHandler::startedLobby() {
    std::cerr << "menuhandler started lobby!" << std::endl;
    queueToMenu.push(MenuAction::StartLobby());
}


// METODOS PARA RECIBIR NOTIFICACIONES DEL PROTOCOLO!
// Para recibir notificaciones de la lobby.
// Notificacion inicial sobre si se pudo crear/unirse a una lobby.
void MenuHandler::createdLobbyDual(const GameContext& context) {
    std::cout << "Lobby creada dual con id " << (int)context.id_lobby << std::endl;
    setLobbyId(context.id_lobby);
    addDuoToLobby();
    // addSoloToLobby();
}
void MenuHandler::createdLobbySolo(const GameContext& context) {
    std::cout << "Lobby creada solo con id " << (int)context.id_lobby << std::endl;
    setLobbyId(context.id_lobby);
    addSoloToLobby();
}

void MenuHandler::joinedLobbyDual(const GameContext& context) {
    std::cout << "Lobby Join dual con id " << (int)context.id_lobby << std::endl;
    setLobbyId(context.id_lobby);
    addDuoToLobby();
}
void MenuHandler::joinedLobbySolo(const GameContext& context) {
    std::cout << "Lobby Join solo con id " << (int)context.id_lobby << std::endl;
    setLobbyId(context.id_lobby);
    addSoloToLobby();
}

void MenuHandler::notifyInfo(GameContext& context, const lobby_info& info) {
    if (info.action == PLAYER_NEW) {
        context.cantidadjugadores++;
        std::cout << "Added.. Total players actual: " << (int)context.cantidadjugadores
                  << std::endl;
        addSoloToLobby();
    } else if (info.action == PLAYER_LEFT) {
        context.cantidadjugadores--;
        std::cout << "Left.. Total players actual: " << (int)context.cantidadjugadores << std::endl;
        playerLeft();
    }
}
