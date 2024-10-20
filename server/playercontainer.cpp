#include "./playercontainer.h"

#include <iostream>

PlayerContainer::PlayerContainer(): last_id(0) {}


// Todo esto no hace falta sincronizar ya que es sincronico!
void PlayerContainer::add(ControlledPlayer* player) {
    // Setea los ids.
    int mx = player->playercount();
    for (int ind = 0; ind < mx; ind++) {
        std::cout << "ADDED IND " << ind << " IS " << last_id + 1 << std::endl;
        player->setid(ind, ++last_id);
    }
    players.push_back(player);
}

// Actualmente el player acceptor se cierra primero.
// Lo que haria que al llegar aca la lista perse debiera estar vacia.
// Pero siempre es bueno verificar.
void PlayerContainer::removeAll() {
    for (auto playerit = players.begin(); playerit != players.end();) {
        if ((*playerit)->disconnect()) {
            std::cerr << "force disconnect " << (*playerit)->getid(0) << " from match" << std::endl;
        }
        playerit = players.erase(playerit);
    }
}
std::vector<player_id> PlayerContainer::updateState(const MatchDto& matchdto) {
    std::vector<player_id> disconnected;

    std::cout << matchdto.parse() << std::endl;  // Show what happened on server.

    for (auto playerit = players.begin(); playerit != players.end();) {
        if ((*playerit)->recvstate(matchdto)) {
            // std::cerr << "NOTIFIED "<< (*playerit)->getid(0) << std::endl;
            ++playerit;
            continue;
        }


        // Agrega/ notifica desconectados.
        int mx = (*playerit)->playercount();
        for (int ind = 0; ind < mx; ind++) {
            // std::cerr << "DISCONNECTED FROM MATCH "<< (*playerit)->getid(ind) << std::endl;
            disconnected.push_back((*playerit)->getid(ind));
        }

        playerit = players.erase(playerit);
    }

    return disconnected;
}
