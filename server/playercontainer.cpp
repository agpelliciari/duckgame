#include "./playercontainer.h"

#include <iostream>
#include <iterator>

#include "./gameerror.h"

PlayerContainer::PlayerContainer(const int _max_players): canceled(false), max_players(_max_players), totalplayers(0), last_id(0) {}


// Todo esto no hace falta sincronizar ya que es sincronico!
void PlayerContainer::add(ControlId& out) {
    if (canceled) {
        throw GameError(LOBBY_NOT_FOUND, "Tried to join to lobby already cancelled");
    }
    
    if(totalplayers+out.getcount() > max_players){
        throw GameError(LOBBY_NO_SPACE, "There was no capacity to join required count");
    }

    if (out.getcount() == 2) {  // Two in the machine!
        int& pos = ids_positions.emplace_back(totalplayers);    
        totalplayers += 2;        
        
        // Antes de agregar el nuevo player. Notifica
        lobby_info info(PLAYER_NEW, pos);
        notifyInfo(info);
        info.data++;
        notifyInfo(info);
        
        out.set(0, ++last_id); // Set first 
        out.set(1, ++last_id); // Set second
        players.emplace_back(out, pos);
        

        return;
    }

    // Por default es 1 solo.
    int& pos = ids_positions.emplace_back(totalplayers);    
    totalplayers += 1;
    
    // Antes de agregar el nuevo player. Notifica
    lobby_info info(PLAYER_NEW, pos);
    notifyInfo(info);
    
    out.set(0, ++last_id); // Set first 
    players.emplace_back(out, pos);
    
}

player_container::iterator PlayerContainer::findit(const ControlId& id){
    auto playerit = players.begin();
    while (playerit->getcontrolid() != id && playerit != players.end()){
        ++playerit;
    }    
    return playerit;
}

ControlledPlayer& PlayerContainer::get(const ControlId& id) {
    auto playerit = findit(id);
    
    if(playerit == players.end()){
         throw GameError(SERVER_ERROR, "Not found id player on container");
    }
    
    return *playerit;
}

bool PlayerContainer::remove(const ControlId& id) {

    auto playerit = findit(id);
    
    if(playerit == players.end()){
        std::cerr << "warning.. At remove, not found player\n";
        return false;
    }
    
    int pos = playerit->getpos();
    int count = id.getcount();
    
    // Look for position to.
    auto posit = ids_positions.begin();
    while (posit != ids_positions.end() && *posit != pos) {
         ++posit;
    }
    if(posit == ids_positions.end()){
         std::cerr << "warning.. At remove, not found player at position\n";
         return false;
    }
    
    // Remove!
    players.erase(playerit);
    posit = ids_positions.erase(posit); // Erase id. So now next one is on curr pos.
    
    totalplayers -= count;

    if(canceled){
        return true; 
    }

    // Update positions after se fueron 'count' por lo que a la pos le restas ese count. 
    while (posit != ids_positions.end()) {
         *posit -= count; 
         ++posit;
    }
        
    
    // Tras actualizar cosas... notifica el remove.
    lobby_info info(PLAYER_LEFT, pos);
    notifyInfo(info);
    count--;
    while(count>0) {
        info.data = ++pos;
        notifyInfo(info);
        count--;
    }
    
    return true;
    
}

// Actualmente el player acceptor se cierra primero.
// Lo que haria que al llegar aca la lista perse debiera estar vacia.
// Pero siempre es bueno verificar.
void PlayerContainer::forceDisconnectAll() {
    canceled = true;
    for (ControlledPlayer& player: players) {
        if (player.canceled()) {
            std::cerr << "force disconnect " << player.toString() << " from match" << std::endl;
        }
    }
}



void PlayerContainer::hostLobbyLeft(const ControlId& host) {
    //players.erase(findit(host)); // Evitemos borrarlo de memoria ahora.
    
    canceled = true;
    lobby_info info(GAME_ERROR, ANFITRION_LEFT);

    // Cuando se va el host no se notifica el disconnect... sino se los desconecta.
    for (ControlledPlayer& player: players) {
        if(player.getcontrolid() == host){
            continue;
        }
        player.recvinfo(info);
        player.canceled();
    }
}
void PlayerContainer::cancelByError(LobbyErrorType cancelError) {
    canceled = true;
    lobby_info info(GAME_ERROR, cancelError);

    // Cuando se va el host no se notifica el disconnect... sino se los desconecta.
    for (ControlledPlayer& player: players) {
        player.recvinfo(info);
        player.canceled();
    }
    totalplayers = 0;
}



void PlayerContainer::finishLobbyMode() {
    for (auto player = players.begin(); player != players.end();) {
          if(player->setgamemode()){
              ++player;
          } else{
              std::cerr << "container should remove " << player->toString() << " at finish lobby mode from match" << std::endl;
              player = players.erase(player); // Elimina los que no esten
          }
    }
}
void PlayerContainer::finishWaitMode() {
    for (auto player = players.begin(); player != players.end();) {
          if(player->setgamemode()){
              ++player;
          } else{
              std::cerr << "container should remove " << player->toString() << " at finish waitmode from match" << std::endl;
              player = players.erase(player); // Elimina los que no esten
          }
    }
}

// Notifica que se empezo la partida. Y cambia a lobby mode.
// El close/cambio de modo es suficiente para saber que empezo.
void PlayerContainer::finishGameMode(const MatchStatsInfo& match_stats) {
    std::cout << "--------------FINISH GAME MODE stats: " << match_stats.parse() << std::endl;
    for (auto player = players.begin(); player != players.end();) {
          if(player->setlobbymode(match_stats)){
              ++player;
          } else{
              std::cerr << "container should remove " << player->toString() << " at finish gamemode from match" << std::endl;
              player = players.erase(player); // Elimina los que no esten
          }
    }
}


void PlayerContainer::putPlayers(std::vector<player_id>& out) const{
    for (auto playerit = players.begin(); playerit != players.end();) {
        int mx = playerit->playercount();
        int base = playerit->getpos();
        for (int ind = 0; ind < mx; ind++) {
            out.push_back(base+ind+1);
            //out.push_back((*playerit).getid(ind));
        }

        ++playerit;
    }
}

std::vector<player_id> PlayerContainer::getPlayers() const {
    std::vector<player_id> connected;
    
    putPlayers(connected);

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

std::vector<player_id> PlayerContainer::updateState(MatchDto& matchdto) {
    std::vector<player_id> disconnected;
    //int ind = 0;
    
    //for (PlayerDTO& player: matchdto.players){
    //     player.id =++ind;
    //}
    
    for (auto playerit = players.begin(); playerit != players.end();) {
        if ((*playerit).recvstate(matchdto)) {
            ++playerit;
            continue;
        }
        // Agrega/ notifica desconectados.
        int mx = playerit->playercount();
        int base = playerit->getpos();
        for (int ind = 0; ind < mx; ind++) {
            disconnected.push_back(base+ind);
            //disconnected.push_back((*playerit).getid(ind));
        }


        std::cerr << "container should remove  " << playerit->toString() << " from match" << std::endl;

        playerit = players.erase(playerit);
    }

    totalplayers -= disconnected.size();
    return disconnected;
}

int PlayerContainer::playercount() const { return totalplayers; }
