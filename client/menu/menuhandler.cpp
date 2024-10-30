#include "menuhandler.h"

#include <utility>

MenuHandler::MenuHandler(LobbyClientSender&& _sender): sender(std::move(_sender)) {}

void MenuHandler::setHostnamePort(std::string hostaname, std::string port) {
    (void)hostaname;
    (void)port;
    std::cout << "Aca se cambia el hostname y port" << std::endl;
}

void MenuHandler::createSoloLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y va a jugar 1 jugador" << std::endl;
}

void MenuHandler::createDuoLobby() {
    std::cout << "Aca se envia que el cliente quiere crear una lobby y van a jugar 2 jugadores" << std::endl;
}

void MenuHandler::joinSoloLobby(int lobbyId) {
    (void)lobbyId;
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con esa id y va a jugar 1 jugador" << std::endl;
}

void MenuHandler::joinDuoLobby(int lobbyId) {
    (void)lobbyId;
    std::cout << "Aca se envia que el cliente quiere unirse a la lobby con esa id y van a jugar 2 jugadores" << std::endl;
}

void MenuHandler::startLobby(std::string map) {
    (void)map;
    std::cout << "Aca se envia que el dueño de la sala quiere empezar el juego con ese map" << std::endl;
}

MenuHandler::~MenuHandler() {}

void MenuHandler::createLobby(uint8_t playercount) {
    sender.createLobby(playercount);
}

void MenuHandler::joinLobby(uint8_t playercount, unsigned int idlobby) {
    sender.joinLobby(playercount, idlobby);
}
