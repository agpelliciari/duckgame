#include "game_loop.h"

#include <cstring>
#include <iostream>
#include <utility>
#include <string>

#include "common/core/liberror.h"

#define ASK_NAME "What is your name?"
#define ACTION_EXIT "Exit"
#define ACTION_PICKUP "Pickup"
#define ACTION_READ "Read"

GameLoop::GameLoop(const char* host, const char* service): protocol(Socket(host, service)) {}
GameLoop::GameLoop(const char* service): GameLoop(NULL, service) {}

// Permitamos el mov desde uno existente para mayor flexibilidad?
GameLoop::GameLoop(Protocol&& prot): protocol(std::move(prot)) {}


unsigned int GameLoop::inputnum() {
    unsigned int res;
    if (!(std::cin >> res)) {
        throw LibError(1, "Could not read number argument");
    }

    return res;
}


bool GameLoop::isrunning(){
     return _is_alive;
}

void GameLoop::startCreateLobby(uint8_t playercount){
    if (_is_alive) {// already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }
    
    LobbyCreateMode* res = new LobbyCreateMode(playercount);
    
    std::unique_ptr<LobbyMode> newmode(res);
    this->mode.swap(newmode);
    start();

    res->startLobby();
}

void GameLoop::startJoinLobby(uint8_t playercount, unsigned int idlobby){
    if (_is_alive) {// already running!!
        throw LibError(1, "Already running client!! finish it first!");
    }

    JoinLobbyMode* res = new JoinLobbyMode(playercount, idlobby);
    
    std::unique_ptr<LobbyMode> newmode(res);
    this->mode.swap(newmode);
    start();
}

void GameLoop::sendMove(char action) {

    PlayerActionDTO dto;
    if (action == 'a') {
        dto.playerind = 0;
        dto.type = MOVE_LEFT;
    } else if (action == 'd') {
        dto.playerind = 0;
        dto.type = MOVE_RIGHT;
    } else if (action == 'j') {
        dto.playerind = 1;
        dto.type = MOVE_LEFT;
    } else if (action == 'l') {
        dto.playerind = 1;
        dto.type = MOVE_RIGHT;
    } else {
        return;
    }
    std::cout << "MOVE " << (int)dto.playerind << " DIR " << (int)dto.type << std::endl;

    protocol.sendaction(dto);
}

void GameLoop::run() {
    mode->exec(protocol); // exec lobby mode.
    
    std::string action;
    // Simple listen de acciones.
    while (_keep_running && std::cin >> action) {
        if (action.compare(ACTION_EXIT) == 0) {
            return;
        }

        if (action.compare(ACTION_READ) == 0) {
            int count = inputnum();

            while (count > 0) {
                std::cout << protocol.recvstate().parse() << std::endl;
                count -= 1;
            }
            continue;
        }
        std::cout << "MOVE " << action << std::endl;
        char* act = action.data();
        int left = action.length();
        int ind = 0;
        while (ind < left) {
            sendMove(*(act + ind));
            ind++;
        }
    }
}


int GameLoop::getcount(){
    std::cout << ASK_NAME << std::endl;

    std::string name;
    if (!(std::getline(std::cin, name, '\n'))) {  // Could not read name.
        throw LibError(1, "Could not read player name");
    }

    std::string name2;

    std::cerr << ASK_NAME << " segundo player" << std::endl;
    if (!(std::getline(std::cin, name2, '\n'))) {  // Could not read name.
        throw LibError(1, "Could not read second player name");
    }

    if (name2.size() > 0) {
        std::cerr << "2 players: " << name << " " << name2 << std::endl;
        return 2;
    }
    std::cerr << "1 player: " << name << std::endl;
    return 1;
}



GameLoop::~GameLoop() {
    if(_is_alive){
       stop();
       
       join();
    }
}
