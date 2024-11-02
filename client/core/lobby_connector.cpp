#include "./lobby_connector.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "./lobby_create_sender.h"
#include "./lobby_join_sender.h"
#include "common/core/liberror.h"

static const char DEFAULT_HOST[] = "127.0.0.1";
static const char DEFAULT_SERVICE[] = "2048";

LobbyConnector::LobbyConnector(GameContext& _context): context(_context), protocol(NULL) {}

void LobbyConnector::setHostnamePort(const std::string& newhost, const std::string& newservice) {

    hostname = newhost.length() == 0 ? std::string(DEFAULT_HOST) : newhost;
    service = newservice.length() == 0 ? std::string(DEFAULT_SERVICE) : newservice;

    std::cout << "Set hostname y port: " << hostname << " : " << service << std::endl;
    // protocol.reset(new ClientProtocol(Socket(host, service)));
}


// Resetea el estado al inicial.
// Y reseteo del protocolo.
// No es una navegacion entre estados perse.
void LobbyConnector::reset() {

    protocol.close();
    // Al hacer close si el state esperando por respuesta del protocolo
    // Tira exception.

    state.reset(NULL);  // El destructor del state actual se encarga si hace falta un join.

    // Reemplazo del protocolo.
    protocol = ClientProtocol(Socket(hostname.c_str(), service.c_str()));
}

bool LobbyConnector::cangonext() { return state.get() != NULL && state->endstate(); }


// Setea el estado para el manejo de lobby
LobbyClientSender* LobbyConnector::setLobbyCreator(LobbyListener& listener, bool dual) {
    std::cout << "Should set state to lobby create " << std::endl;
    context.dualplay = dual;

    LobbyCreateSender* creator = new LobbyCreateSender(protocol, context, listener);
    state.reset(creator);

    // Ahora empeza el thread. Despues de joinear el anterior.
    creator->createLobby();

    return creator;
}

void LobbyConnector::setLobbyJoin(LobbyListener& listener, bool dual, unsigned int lobbyid) {
    std::cout << "Should set state to lobby join " << lobbyid << std::endl;
    context.dualplay = dual;
    context.id_lobby = lobbyid;

    LobbyJoinSender* joiner = new LobbyJoinSender(protocol, context, listener);
    state.reset(joiner);

    // Ahora empeza el thread. Despues de joinear el anterior.
    joiner->joinLobby();
}

// Utiliza el protocol del sender, le quita el
GameActionSender* LobbyConnector::initGame(EventListener& listener) {
    GameActionSender* game = new GameActionSender(protocol, listener, context);
    state.reset(game);
    return game;
}

LobbyConnector::~LobbyConnector() {
    protocol.close();

    state.reset(NULL);  // Libera el state si hay. El pointer lo haria igual.
}
