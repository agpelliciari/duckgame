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

LobbyConnector::LobbyConnector(GameContext& _context): context(_context), skt(std::nullopt) {}

void LobbyConnector::setHostnamePort(const std::string& newhost, const std::string& newservice) {

    hostname = newhost.length() == 0 ? std::string(DEFAULT_HOST) : newhost;
    service = newservice.length() == 0 ? std::string(DEFAULT_SERVICE) : newservice;

    std::cout << "Set hostname y port: " << hostname << " : " << service << std::endl;
}


void LobbyConnector::clear() {

    skt.value().finish();
    // Al hacer close si el state esperando por respuesta del socket
    // Tira exception.
    // No se libera... por que podria traer problemas.
    state.reset(NULL);  // El destructor del state actual se encarga si hace falta un join.

    skt.reset();
}

// Resetea el estado al inicial.
// Y reseteo del protocolo.
// No es una navegacion entre estados perse.
void LobbyConnector::reset() {
    if (skt.has_value()) {
        clear();
    }

    // Reemplazo del protocolo.
    skt.emplace(hostname.c_str(), service.c_str());
}

bool LobbyConnector::cangonext() { return state.get() != NULL && state->endstate(); }


// Setea el estado para el manejo de lobby
LobbyClientSender* LobbyConnector::setLobbyCreator(LobbyListener& listener, bool dual) {
    std::cout << "Should set state to lobby create " << std::endl;
    context.dualplay = dual;
    context.cantidadjugadores = dual ? 2 : 1;


    LobbyCreateSender* creator = new LobbyCreateSender(skt.value(), context, listener);
    state.reset(creator);

    // Ahora empeza el thread. Despues de joinear el anterior.
    creator->createLobby();

    return &(creator->getSender());
}

void LobbyConnector::setLobbyJoin(LobbyListener& listener, bool dual, unsigned int lobbyid) {
    std::cout << "Should set state to lobby join " << lobbyid << std::endl;
    context.dualplay = dual;
    context.id_lobby = lobbyid;

    LobbyJoinSender* joiner = new LobbyJoinSender(skt.value(), context, listener);
    state.reset(joiner);

    // Ahora empeza el thread. Despues de joinear el anterior.
    joiner->joinLobby();
}

// Utiliza el protocol del sender, le quita el
GameActionSender* LobbyConnector::initGame(EventListener& listener) {
    GameActionSender* game = new GameActionSender(skt.value(), listener, context);
    state.reset(game);
    return game;
}

LobbyConnector::~LobbyConnector() {
    if (skt.has_value()) {
        clear();
    }
}


// Metodos getters para la configuracion.

int LobbyConnector::getTotalPlayers() const { return context.cantidadjugadores; }

bool LobbyConnector::isdual() const { return context.dualplay; }
