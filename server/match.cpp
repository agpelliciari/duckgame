#include "./match.h"

#include <iostream>

#include "./gameerror.h"
//#include <thread>
#include "common/clock.h"

Match::Match(lobbyID _id): id(_id), players(), looper(), connectedplayers(0), map() {}


// Protected// friend accessed methods
ControlledPlayer& Match::addPlayers(uint8_t count) {
    ControlledPlayer& player = players.add(count);

    // Se suma despues porque el add puede fallar!
    // Por capacidad o por que esta cancelada!
    connectedplayers++;  // Solo importa la cantidad de conectados...


    return player;
}
int Match::playercount() const { return players.playercount(); }


bool Match::notifyDisconnect(ControlledPlayer& player) {
    connectedplayers--;  // Solo importa la cantidad de conectados
    if (player.disconnect()) {
        // Si se esta desconectando ahora entonces notifica.
        std::cout << "Disconnected player from match? now " << connectedplayers << std::endl;
        if (_keep_running) {
            return connectedplayers == 0;
        }

        players.remove(player);
    }
    return connectedplayers == 0;
}

void Match::init(MapLoader& maps, const char* mapname) {
    if (is_alive()) {
        throw GameError(LOBBY_ALREADY_STARTED, "Tried to start a match already started!!\n");
    }
    MapDeserializer& deserial = maps.getLoader(mapname);

    deserial.loadMapInfo(map);

    // Notify/start players. Ya podrian enviar la info del mapa.
    looper.start_players(players);
    players.finishLobbyMode();


    // Carga info para el server
    struct ObjectsInfo objects;

    deserial.loadObjectsInfo(objects);

    // Se podria hacer un merge de bloques! A la forma greedy
    objects.blocks.reserve(map.blocks.size());
    for (const struct BlockDTO& block: map.blocks) {
        objects.blocks.emplace_back(block.pos.x, block.pos.y);
    }

    looper.add_objects(objects);

    start();
    // match_start.notify_all();
}

bool Match::hostLobbyLeft(ControlledPlayer& host) {
    connectedplayers--;
    if (connectedplayers == 0) {
        host.disconnect();
        return true;
    }
    // Notifica a los otros ademas del disconnect.
    host.disconnect();
    players.hostLobbyLeft(host);

    return false;
}

void Match::cancelByError(LobbyErrorType error) { players.cancelByError(error); }


// General/public methods.

bool Match::operator==(const Match& other) const { return this->id == other.id; }


lobbyID Match::getID() const { return this->id; }

// Metodos delegatorios.
void Match::notifyAction(const PlayerActionDTO& action) {
    if (_keep_running) {
        looper.pushAction(action);
    }
}

const MatchStatsInfo& Match::getStats() const{
     return this->stats;
}

void Match::run() {

    looper.playRound(players,this->stats);
    players.finishGameMode(); // Notify/move players to lobby mode.
    // Notifier will check wether to send stats or so
    
    Clock timer(1000); // Timer de a pasos de 1 segundo.
    while(_keep_running && this->stats.state == PAUSADA){
         // Wait 5 seconds?
         timer.resetnext();
         int mx = 5;
         lobby_info info(MATCH_PAUSE_TICK, mx);
         
         while(_keep_running && timer.tickcount() < mx){
             info.data = mx-timer.tickcount();
             players.notifyInfo(info);
             timer.tickRest(); // sleep for 1 second if so is needed
         }
         
         // Go next round/s
         if(_keep_running){
             info.action = MATCH_PAUSE_END;
             info.data = 0;// reset data 
             
             players.notifyInfo(info);
             players.finishLobbyMode();
             looper.playRound(players,this->stats);
             players.finishGameMode(); // Notify/move players to lobby mode.
         }
    }
    
    // Checkea si el finish fue natural o forzado.

    // notifica los playeres. Del final.
    players.forceDisconnectAll();
}

bool Match::isrunning() const { return _is_alive; }

const MapInfo& Match::getMap() const { return map; }


void Match::finish(MapLoader& maps) {
    maps.removeLoader(map.map_id);

    if (_keep_running) {
        stop();
        looper.stop();
        join();
        return;
    }
    // El finish en caso de no estar corriendo.
    // Asume que se esta en lobby mode.
    players.forceDisconnectAll();
}

Match::~Match() {
    if (_keep_running) {
        stop();
        looper.stop();
        join();
    }
}
