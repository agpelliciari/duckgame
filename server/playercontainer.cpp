#include "./playercontainer.h"

#include <iostream>

PlayerContainer::PlayerContainer(): last_id(0) {}


// Todo esto no hace falta sincronizar ya que es sincronico!
ControlledPlayer& PlayerContainer::add(uint8_t countplayers) {

    ControlledPlayer& player = players.emplace_back(countplayers);
    for (uint8_t ind = 0; ind < countplayers; ind++) {
        player.setid(ind, ++last_id);
    }

    return player;
}

// Actualmente el player acceptor se cierra primero.
// Lo que haria que al llegar aca la lista perse debiera estar vacia.
// Pero siempre es bueno verificar.
void PlayerContainer::removeAll() {
    for (auto playerit = players.begin(); playerit != players.end();) {
        if ((*playerit).disconnect()) {
            std::cerr << "force disconnect " << (*playerit).toString() << " from match"
                      << std::endl;
        }
        playerit = players.erase(playerit);
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

std::vector<player_id> PlayerContainer::updateState(const MatchDto& matchdto) {
    std::vector<player_id> disconnected;

    std::cout << matchdto.parse() << std::endl;  // Show what happened on server.

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

    return disconnected;
}
