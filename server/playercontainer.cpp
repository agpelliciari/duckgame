#include "./playercontainer.h"

#include <iostream>

PlayerContainer::PlayerContainer() {}

void PlayerContainer::add(Player* player) {
    std::unique_lock<std::mutex> lck(mtx);  // Evitemos se mande una notificacion y asi
    players.push_back(player);
}


void PlayerContainer::remove(Player* player) {
    std::unique_lock<std::mutex> lck(mtx);  // Evitemos se mande una notificacion y asi

    // Despues del lock para asegurarse no se le esta mandando Algo.
    // Podria estar en el destructor. Pero mejor explicito.
    player->close();
    players.remove(player);
}


// Actualmente el player acceptor se cierra primero.
// Lo que haria que al llegar aca la lista perse debiera estar vacia.
// Pero siempre es bueno verificar.
void PlayerContainer::removeAll() {
    std::unique_lock<std::mutex> lck(mtx);  // Evitemos se mande una notificacion y asi

    for (auto playerit = players.begin(); playerit != players.end();) {
        (*playerit)->close();
        playerit = players.erase(playerit);
    }
}
void PlayerContainer::receiveEvent(const Event&& event) {
    std::unique_lock<std::mutex> lck(mtx);  // Evitemos se unan mas players.

    std::cout << event.parseinfo() << std::endl;  // Show what happened on server.

    for (auto playerit = players.begin(); playerit != players.end();) {
        (*playerit)->recvevent(event);
        ++playerit;
    }
}
