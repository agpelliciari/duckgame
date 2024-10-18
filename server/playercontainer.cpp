#include "./playercontainer.h"

#include <iostream>

PlayerContainer::PlayerContainer():last_id(1) {}


// Todo esto no hace falta sincronizar ya que es sincronico!
void PlayerContainer::add(Player* player) {
    // Setea los ids.
    int mx = player->playercount();
    for(int ind = 0; ind < mx; ind++){
        player->setid(ind, ++last_id); 
    }
    players.push_back(player);
    
}

// Actualmente el player acceptor se cierra primero.
// Lo que haria que al llegar aca la lista perse debiera estar vacia.
// Pero siempre es bueno verificar.
void PlayerContainer::removeAll() {
    for (auto playerit = players.begin(); playerit != players.end();) {
        playerit = players.erase(playerit);
    }
}
std::vector<player_id> PlayerContainer::receiveEvent(const Event&& event) {    
    std::vector<player_id> disconnected;
    std::cout << event.parseinfo() << std::endl;  // Show what happened on server.

    for (auto playerit = players.begin(); playerit != players.end();) {
        if((*playerit)->recvevent(event)){
            ++playerit;
            continue;
        }
        
        // Agrega/ notifica desconectados.
        int mx = (*playerit)->playercount();
        for(int ind = 0; ind < mx; ind++){
            disconnected.push_back((*playerit)->getid(ind)); 
        }
        
        playerit = players.erase(playerit);
        
    }
    
    return disconnected;
}
