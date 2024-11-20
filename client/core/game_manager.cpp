#include "./game_manager.h"

#include <cstring>
#include <iostream>
#include <string>
#include <utility>

#include "common/core/liberror.h"
#include "lobby/lobby_create_state.h"
#include "lobby/lobby_join_state.h"

static const char DEFAULT_HOST[] = "127.0.0.1";
static const char DEFAULT_SERVICE[] = "2048";

GameManager::GameManager(GameContext& _context): context(_context), skt(std::nullopt) {}

void GameManager::setHostnamePort(const std::string& newhost, const std::string& newservice) {

    hostname = newhost.length() == 0 ? std::string(DEFAULT_HOST) : newhost;
    service = newservice.length() == 0 ? std::string(DEFAULT_SERVICE) : newservice;

    std::cout << "Set hostname y port: " << hostname << " : " << service << std::endl;
}


void GameManager::clear() {
    // El state deberia encargarse de cerrar el protocol/skt si esta bloqueado por este.
    state.reset(NULL);  // El destructor del state actual se encarga si hace falta un join.

    skt.reset();
}

// Resetea el estado al inicial.
// Y reseteo del protocolo.
// No es una navegacion entre estados perse.
bool GameManager::reset() {
    if (skt.has_value()) {
        clear();
    }

    try {
        // Reemplazo del protocolo.
        skt.emplace(hostname.c_str(), service.c_str());
        return false;
    } catch (const std::exception& err) {
        std::cerr << "Connection reset failed: " << err.what() << "\n";
        return true;
    } catch (...) {
        std::cerr << "Connection reset failed.. unknown error\n";
        return true;
    }
}

bool GameManager::cangonext() { return state.get() != NULL && state->endstate(); }


// Setea el estado para el manejo de lobby
LobbyActionQueue* GameManager::setLobbyCreator(LobbyListener& listener, bool dual) {
    std::cout << "Should set state to lobby create " << std::endl;
    context.dualplay = dual;
    context.players.clear();
    //context.cantidadjugadores = dual ? 2 : 1;


    LobbyCreateState* creator = new LobbyCreateState(skt.value(), context, listener);
    state.reset(creator);

    // Ahora empeza el thread. Despues de joinear el anterior.
    creator->createLobby();

    return &(creator->getSender());
}

void GameManager::setLobbyJoin(LobbyListener& listener, bool dual, unsigned int lobbyid) {
    std::cout << "Should set state to lobby join " << lobbyid << std::endl;
    context.dualplay = dual;
    context.id_lobby = lobbyid;
    context.players.clear();

    LobbyJoinState* joiner = new LobbyJoinState(skt.value(), context, listener);
    state.reset(joiner);

    // Ahora empeza el thread. Despues de joinear el anterior.
    joiner->joinLobby();
}

// Utiliza el protocol del sender, le quita el
PlayStateSender* GameManager::initGame(EventListener& listener) {
    context.cantidadjugadores = context.players.size();

    PlayStateSender* game = new PlayStateSender(skt.value(), listener, context);
    state.reset(game);
    return game;
}

GameManager::~GameManager() {
    if (skt.has_value()) {
        clear();
    }
}


// Metodos getters para la configuracion.

int GameManager::getTotalPlayers() const { return context.players.size(); }

bool GameManager::isdual() const { return context.dualplay; }
