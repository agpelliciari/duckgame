#include "./match.h"

#include <iostream>

#define MS_SECOND 1000
#define PAUSE_SECONDS 5
#define AFTER_ROUND_SECONDS 3

#include "./gameerror.h"
//#include <thread>
#include "common/clock.h"

Match::Match(lobbyID _id, const int max_players): id(_id), players(max_players), looper(), connectedplayers(0), map() {}


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

void Match::loadMap(MapDeserializer& deserial){
    deserial.loadMapInfo(map);

    // Carga info para el server
    objects = ObjectsInfo(map.size.x,map.size.y);

    deserial.loadObjectsInfo(objects);

    // Se podria hacer un merge de bloques! A la forma greedy
    objects.blocks.reserve(map.blocks.size());
    for (const struct BlockDTO& block: map.blocks) {
        objects.blocks.emplace_back(block.pos.x, block.pos.y);
    }
    //try{
    //    return true;
    //} catch()
}

void Match::init(MapLoader& maps, const char* mapname) {
    if (is_alive()) {
        throw GameError(LOBBY_ALREADY_STARTED, "Tried to start a match already started!!\n");
    }    
    
    loadMap(maps.getLoader(mapname));
    std::cout << "INIT MATCH AFTER LOAD MAP?\n";
    // Notify/start players. Ya podrian enviar la info del mapa.
    looper.start_players(players, stats);
    looper.add_objects(objects);
    players.finishLobbyMode();

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
    if (stats.state == INICIADA) {
        looper.pushAction(action);
    }
}

const MatchStatsInfo& Match::getStats() const{
     return this->stats;
}

bool Match::pauseMatch(int count_seconds){
    Clock timer(MS_SECOND);  // Timer de a pasos de 1 segundo.
    timer.resetnext();
    lobby_info info(MATCH_PAUSE_TICK, count_seconds);

    while (_keep_running && timer.tickcount() < count_seconds) {
        info.data = count_seconds - timer.tickcount();
        players.notifyInfo(info);
        timer.tickRest();  // sleep for 1 second if so is needed
    }
    
    //timer.tickcount() >= mx
    // No se envia si se cancelo con la 'q' en el medio. Se handlea despues?
    if (_keep_running) { 
        info.action = MATCH_PAUSE_END;
        info.data = 0;  // reset data

        players.notifyInfo(info);
        return true;
    }
    
    return false;
}

bool Match::handlePostRound(){
    if(this->stats.isRunning()){
        players.finishGameMode(this->stats);  // Notify/move players to lobby mode.
        
        bool handled = pauseMatch(this->stats.isPaused()? PAUSE_SECONDS : AFTER_ROUND_SECONDS);
        
        players.finishLobbyMode(); 
        return handled;
    }
    
    return false;
}

void Match::run() {

    looper.playRound(players, this->stats);
    while (_keep_running && handlePostRound()) {
        //looper.start_players(players, stats);
        // re envia info del mapa?
        looper.reset_objects(objects);
        looper.reset_players(players);
        
        looper.playRound(players, this->stats);
    }

    if (this->stats.isRunning()) {
        std::cout << "NOT FINISHED? FORCE CANCEL!\n";
        this->stats.state = CANCELADA;
    } else{
        std::cout << "FINISHED MATCH? NOTIFY!!! "<< stats.parse()<<" \n";    
    }
    players.finishGameMode(this->stats);

    // Checkea si el finish fue natural o forzado.

    // notifica los playeres. Del final.
    players.forceDisconnectAll();
}

bool Match::isrunning() const { return stats.isRunning(); }

const MapInfo& Match::getMap() const { return map; }

std::vector<player_id> Match::getPlayers() const { return players.getPlayers(); }


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
