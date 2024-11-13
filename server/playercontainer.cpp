#include "./playercontainer.h"

#include <iostream>

#include "./gameerror.h"

PlayerContainer::PlayerContainer(): canceled(false), totalplayers(0), last_id(0) {}


// Todo esto no hace falta sincronizar ya que es sincronico!
ControlledPlayer& PlayerContainer::add(uint8_t countplayers) {
    if (canceled) {
        throw GameError(LOBBY_NOT_FOUND, "Tried to join to lobby already cancelled");
    }

    // totalplayers no es perse el id para el player
    // conceptualmente es distinto.
    // Por ahora pareceria es lo mismo que el id.
    // Pero a la hora de remove. No parece correcto. Si bien por ahora no se necesita se puedan
    // conectar.
    if (countplayers == 2) {  // Two in the machine!
        totalplayers += 2;
        player_id first = ++last_id;
        lobby_info info(PLAYER_NEW, first);
        notifyInfo(info);
        info.data = ++last_id;
        notifyInfo(info);

        return players.emplace_back(first, last_id);
    }

    // Por default es 1 solo.
    totalplayers += 1;
    lobby_info info(PLAYER_NEW, ++last_id);
    notifyInfo(info);
    return players.emplace_back(last_id);
}

void PlayerContainer::remove(const ControlledPlayer& player) {
    int mx = player.playercount();
    totalplayers -= mx;

    std::vector<lobby_info> disconnected;
    disconnected.reserve(mx);
    for (int ind = 0; ind < mx; ind++) {
        disconnected.emplace_back(PLAYER_LEFT, player.getid(ind));
    }

    players.remove(player);

    for (const lobby_info& info: disconnected) {
        notifyInfo(info);
    }
}

// Actualmente el player acceptor se cierra primero.
// Lo que haria que al llegar aca la lista perse debiera estar vacia.
// Pero siempre es bueno verificar.
void PlayerContainer::forceDisconnectAll() {
    for (ControlledPlayer& player: players) {
        if (player.disconnect()) {
            std::cerr << "force disconnect " << player.toString() << " from match" << std::endl;
        }
    }
    /*
    for (auto playerit = players.begin(); playerit != players.end();) {
        if ((*playerit).disconnect()) {
            std::cerr << "force disconnect " << (*playerit).toString() << " from match"
                      << std::endl;
        }
        playerit = players.erase(playerit);
    }

    */
}

void PlayerContainer::finishLobbyMode() {
    for (ControlledPlayer& player: players) {
        player.setgamemode();
    }
}

void PlayerContainer::hostLobbyLeft(const ControlledPlayer& host) {
    players.remove(host);
    cancelByError(ANFITRION_LEFT);
}
void PlayerContainer::cancelByError(LobbyErrorType cancelError) {
    canceled = true;
    lobby_info info(GAME_ERROR, cancelError);

    // Cuando se va el host no se notifica el disconnect... sino se los desconecta.
    for (ControlledPlayer& player: players) {
        player.recvinfo(info);
        player.disconnect();
    }
    totalplayers = 0;
}


// Notifica que se empezo la partida. Y cambia a lobby mode.
// El close/cambio de modo es suficiente para saber que empezo.
void PlayerContainer::finishGameMode() {
    for (ControlledPlayer& player: players) {
        player.setlobbymode();
    }
}

std::vector<player_id> PlayerContainer::getPlayers() {
    std::vector<player_id> connected;
    for (auto playerit = players.begin(); playerit != players.end();) {
        int mx = (*playerit).playercount();
        for (int ind = 0; ind < mx; ind++) {
            connected.push_back((*playerit).getid(ind));
        }

        ++playerit;
    }

    return connected;
}

// No nos fijamos si se desconectaron. En fase lobby el lobby container se encarga de notificar.
// Lo hacen por medio del remove... Por eso no se verifica si el recvinfo dio true o no.
void PlayerContainer::notifyInfo(const lobby_info& info) {
    for (ControlledPlayer& player: players) {
        // std::cout << "NOTIFYING INFO TO "<< player.toString()<<"!! " << (int)info.action << ".. "
        // << (int)info.data << std::endl;
        player.recvinfo(info);
    }
}

std::vector<player_id> PlayerContainer::updateState(const MatchDto& matchdto) {
    std::vector<player_id> disconnected;

    for (auto playerit = players.begin(); playerit != players.end();) {
        if ((*playerit).recvstate(matchdto)) {
            ++playerit;
            continue;
        }
        // Agrega/ notifica desconectados.
        int mx = (*playerit).playercount();
        for (int ind = 0; ind < mx; ind++) {
            disconnected.push_back((*playerit).getid(ind));
        }

        std::cerr << "disconnected " << (*playerit).toString() << " from match" << std::endl;

        playerit = players.erase(playerit);
    }

    totalplayers -= disconnected.size();
    return disconnected;
}

int PlayerContainer::playercount() const { return totalplayers; }
