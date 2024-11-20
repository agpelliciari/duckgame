#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <cstdint>
#include <string>
#include <vector>

#include "common/clientprotocol.h"
#include "common/dtosmap.h"

//#define MAP_BLOCK_UNIT 16
//#include <list>
#include <vector>

struct GameContext {
    unsigned int id_lobby;  // cppcheck-suppress unusedStructMember

    bool started;

    bool dualplay;          // cppcheck-suppress unusedStructMember
    uint8_t first_player;   // cppcheck-suppress unusedStructMember
    uint8_t second_player;  // cppcheck-suppress unusedStructMember


    struct MapData map;  // cppcheck-suppress unusedStructMember

    uint8_t max_player_count;
    int cantidadjugadores;
    std::vector<int> players;
    
    
    void removePlayer(int id){
        for (auto playerit = players.begin(); playerit != players.end();) {
            if(*playerit == id){
                players.erase(playerit);
                return;
            }
            ++playerit;
        }
    }

    void addPlayer(int id){
        players.push_back(id);
    }



    GameContext():
            id_lobby(0),
            started(false),
            dualplay(true),
            first_player(1),
            second_player(2),
            map(),
            max_player_count(4) {}
};

#endif
