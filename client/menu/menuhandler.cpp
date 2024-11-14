#include "menuhandler.h"

#include <utility>

MenuHandler::MenuHandler(GameManager& _connector): connector(_connector), sender(NULL) {}

void MenuHandler::onSetHostnamePort(const std::string& hostname, const std::string& port) {
    connector.setHostnamePort(hostname, port);
}

// Se hace el update del protocol en el sender cada vez se haga un llamado.
// Por si algo fallo.
void MenuHandler::onCreateSoloLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y va a jugar 1 jugador"
              << std::endl;

    if (connector.reset()) {  // Si fallo el reset ... no hagas nada
        canceledLobby("Fallo la conexion");
        return;
    }
    sender = connector.setLobbyCreator(*this, false);
}

void MenuHandler::onCreateDuoLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y van a jugar 2 jugadores"
              << std::endl;

    if (connector.reset()) {
        canceledLobby("Fallo la conexion");
        return;
    }
    sender = connector.setLobbyCreator(*this, true);
}

void MenuHandler::onJoinSoloLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y va a jugar 1 jugador" << std::endl;

    // Reset protocol and curr state si existe.
    // Si falla retorna true
    if (connector.reset()) {
        canceledLobby("Fallo la conexion");
        return;
    }

    connector.setLobbyJoin(*this, false, lobbyId);
    sender = NULL;  // El que joinea no manda cosas?
    // setLobbyId(lobbyId);
    //  TODO: Llamar a addSoloToLobby o addDuoToLobby
    //  dependiendo de si en el lobby el host es de 1 o 2
}

void MenuHandler::onJoinDuoLobby(int lobbyId) {
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con id: " << lobbyId
              << " y van a jugar 2 jugadores" << std::endl;

    if (connector.reset()) {
        canceledLobby("Fallo la conexion");
        return;
    }

    connector.setLobbyJoin(*this, true, lobbyId);
    sender = NULL;
    // setLobbyId(lobbyId);
    //  TODO: Llamar a addSoloToLobby o addDuoToLobby
    //  dependiendo de si en el lobby el host es de 1 o 2
}

void MenuHandler::onStartLobby(const std::string& map) {
    std::cout << "Empeza con el mapa: " << map << std::endl;
    sender->notifyStart(map);
}

void MenuHandler::onCancelLobby() {  // Cuando el Host da click en el boton de cancel en lugar de
                                     // start
    connector.clear();
    // sender->notifyCancel();
}


bool MenuHandler::tryPopActionToMenu(MenuAction& actionToMenu) {
    return queueToMenu.try_pop(actionToMenu);
}

MenuHandler::~MenuHandler() {}


// Acciones a menu...
void MenuHandler::setLobbyId(int lobbyId) { queueToMenu.push(MenuAction::SetLobbyId(lobbyId)); }
void MenuHandler::setLobbyMaps(const std::vector<std::string>& maps) { queueToMenu.push(MenuAction::SetLobbyMaps(maps)); }

void MenuHandler::addSoloToLobby() { queueToMenu.push(MenuAction::AddSoloToLobby()); }
void MenuHandler::addDuoToLobby() { queueToMenu.push(MenuAction::AddDuoToLobby()); }
void MenuHandler::removePlayerFromLobby() { queueToMenu.push(MenuAction::RemovePlayerFromLobby()); }

// Acciones a menu.. Llamados/notificaciones directas ...
// Se podria pasar el codigo de error si se quiere mostrar un mensaje personalizado.
void MenuHandler::startedLobby() { queueToMenu.push(MenuAction::StartLobby()); }
void MenuHandler::canceledLobby(const char* msg) {
    std::cout << "Canceled lobby " << msg << std::endl;
    queueToMenu.push(MenuAction::CancelLobby(msg));
}

void MenuHandler::failedCreate(const char* msg) {
    std::cout << "Failed create " << msg << std::endl;
    queueToMenu.push(MenuAction::FailCreate(msg));
}
void MenuHandler::failedJoin(const char* msg) {
    std::cout << "Failed join " << msg << std::endl;
    queueToMenu.push(MenuAction::FailJoin(msg));
}


// Tambien son directas ahora
void MenuHandler::playerJoinedLobby(int id) {
    std::cout << "New player " << id << ".. Total: " << connector.getTotalPlayers() << std::endl;
    addSoloToLobby();
}

void MenuHandler::playerLeftLobby(int id) {
    std::cout << "Player  " << id << " left .. Total: " << connector.getTotalPlayers() << std::endl;
    removePlayerFromLobby();
}

// METODOS PARA RECIBIR NOTIFICACIONES DEL PROTOCOLO!
// Para recibir notificaciones de la lobby.
// Notificacion inicial sobre si se pudo crear/unirse a una lobby.
void MenuHandler::createdLobbyDual(unsigned int id_lobby) {
    std::cout << "Lobby creada dual con id " << id_lobby << std::endl;
    setLobbyId(id_lobby);
    std::vector<std::string> maps = {"Mapa1", "Mapa2", "Mapa3"};
    setLobbyMaps(maps);
    addDuoToLobby();
}
void MenuHandler::createdLobbySolo(unsigned int id_lobby) {
    std::cout << "Lobby creada solo con id " << id_lobby << std::endl;
    setLobbyId(id_lobby);
    std::vector<std::string> maps = {"Mapa1", "Mapa2", "Mapa3"};
    setLobbyMaps(maps);
    addSoloToLobby();
}

void MenuHandler::joinedLobbyDual(const GameContext& context) {
    std::cout << "Lobby Join dual con id " << (int)context.id_lobby << " count there "
              << context.cantidadjugadores << std::endl;
    setLobbyId(context.id_lobby);

    for (int i = 0; i < context.cantidadjugadores; i++) {
        addSoloToLobby();  // esto agrega los nuevos players que existen
    }
}
void MenuHandler::joinedLobbySolo(const GameContext& context) {
    std::cout << "Lobby Join solo con id " << (int)context.id_lobby << " count there "
              << context.cantidadjugadores << std::endl;
    setLobbyId(context.id_lobby);

    for (int i = 0; i < context.cantidadjugadores; i++) {
        addSoloToLobby();  // esto agrega los nuevos players que existen
    }
}
