#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <cstdint>
#include "common/clientprotocol.h"

class GameContext {
public:
    unsigned int id_lobby;  // cppcheck-suppress unusedStructMember

    bool started;
    bool dualplay;          // cppcheck-suppress unusedStructMember


    struct MapData map;  // cppcheck-suppress unusedStructMember

    uint8_t max_player_count;
    uint8_t first_player;   // cppcheck-suppress unusedStructMember
    uint8_t second_player;  // cppcheck-suppress unusedStructMember
    int cantidadjugadores;  // cppcheck-suppress unusedStructMember
    
    int wins_needed;
    int rounds_per_set;
    
    int countPlayers() const;
    void removePlayer(uint8_t pos);
    void addPlayer(uint8_t pos);
    
    void reset();
    GameContext();
};

#endif
