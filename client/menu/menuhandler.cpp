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
    sender = connector.setLobbyCreator(*this);
    sender->createLobby(false);
}

void MenuHandler::onCreateDuoLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y van a jugar 2 jugadores"
              << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyCreator(*this);
    sender->createLobby(true);
}

void MenuHandler::onJoinSoloLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y va a jugar 1 jugador" << std::endl;

    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyJoin(*this, lobbyId);
    sender->joinLobby(false, lobbyId);
}

void MenuHandler::onJoinDuoLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y van a jugar 2 jugadores" << std::endl;
    connector.reset();  // Reset protocol and curr state si existe.
    sender = connector.setLobbyJoin(*this, lobbyId);
    sender->joinLobby(true, lobbyId);
}

void MenuHandler::onStartLobby(const std::string& map) {
    std::cout << "Empeza con el mapa: " << map << std::endl;
    sender->notifyStart();
}

void MenuHandler::onCancelLobby() {  // Cuando el Host da click en el boton de cancel en lugar de
                                     // start
    sender->notifyCancel();
}


bool MenuHandler::tryPopActionToMenu(MenuAction& actionToMenu) {
    return queueToMenu.try_pop(actionToMenu);
}

MenuHandler::~MenuHandler() {}


// Acciones a menu...
void MenuHandler::setLobbyId(int lobbyId) { queueToMenu.push(MenuAction::SetLobbyId(lobbyId)); }

void MenuHandler::addSoloToLobby() { queueToMenu.push(MenuAction::AddSoloToLobby()); }
void MenuHandler::addDuoToLobby() { queueToMenu.push(MenuAction::AddDuoToLobby()); }
void MenuHandler::removePlayerFromLobby() { queueToMenu.push(MenuAction::RemovePlayerFromLobby()); }

// Acciones a menu.. Llamados/notificaciones directas ...
// Se podria pasar el codigo de error si se quiere mostrar un mensaje personalizado.
void MenuHandler::startedLobby() { queueToMenu.push(MenuAction::StartLobby()); }
void MenuHandler::canceledLobby() { queueToMenu.push(MenuAction::CancelLobby()); }

void MenuHandler::failedCreate() { queueToMenu.push(MenuAction::FailCreate()); }
void MenuHandler::failedJoin() { queueToMenu.push(MenuAction::FailJoin()); }


// METODOS PARA RECIBIR NOTIFICACIONES DEL PROTOCOLO!
// Para recibir notificaciones de la lobby.
// Notificacion inicial sobre si se pudo crear/unirse a una lobby.
void MenuHandler::createdLobbyDual(const GameContext& context) {
    std::cout << "Lobby creada dual con id " << (int)context.id_lobby << std::endl;
    setLobbyId(context.id_lobby);
    addDuoToLobby();
}
void MenuHandler::createdLobbySolo(const GameContext& context) {
    std::cout << "Lobby creada solo con id " << (int)context.id_lobby << std::endl;
    setLobbyId(context.id_lobby);
    addSoloToLobby();
}

void MenuHandler::joinedLobbyDual(const GameContext& context) {
    std::cout << "Lobby Join dual con id " << (int)context.id_lobby << std::endl;
    setLobbyId(context.id_lobby);
    addDuoToLobby();  // esto agrega los nuevos players que se unen
    // faltan agregar los players que YA estaban en la sala
}
void MenuHandler::joinedLobbySolo(const GameContext& context) {
    std::cout << "Lobby Join solo con id " << (int)context.id_lobby << std::endl;
    setLobbyId(context.id_lobby);
    addSoloToLobby();  // esto agrega los nuevos players que se unen
    // faltan agregar los players que YA estaban en la sala
}

void MenuHandler::notifyInfo(const GameContext& context, const lobby_info& info) {
    if (info.action == JOIN_LOBBY) {
        std::cout << "Added.. Total players actual: " << context.cantidadjugadores << std::endl;
        addSoloToLobby();
    } else if (info.action == LEAVE_LOBBY) {
        std::cout << "Left.. Total players actual: " << context.cantidadjugadores << std::endl;
        removePlayerFromLobby();
    }
}
