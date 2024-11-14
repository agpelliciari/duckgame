#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <cstdint>
#include <string>
#include <vector>

#include "common/clientprotocol.h"
#include "common/dtosmap.h"

#define MAP_BLOCK_UNIT 16


struct GameContext {
    unsigned int id_lobby;  // cppcheck-suppress unusedStructMember

    bool started;

    bool dualplay;          // cppcheck-suppress unusedStructMember
    uint8_t first_player;   // cppcheck-suppress unusedStructMember
    uint8_t second_player;  // cppcheck-suppress unusedStructMember


    struct MapData map;  // cppcheck-suppress unusedStructMember

    uint8_t cantidadjugadores;  // No hace falta? El dto match lo dira

    GameContext():
            id_lobby(0),
            started(false),
            dualplay(true),
            first_player(1),
            second_player(2),
            map(),
            cantidadjugadores(4) {}
};

#endif
