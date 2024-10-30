#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <cstdint>
#include <vector>

#include "common/dtosobject.h"

struct GameContext {
    unsigned int id_lobby;  // cppcheck-suppress unusedStructMember

    bool dualplay;          // cppcheck-suppress unusedStructMember
    uint8_t first_player;   // cppcheck-suppress unusedStructMember
    uint8_t second_player;  // cppcheck-suppress unusedStructMember

    int map_size_x;                // cppcheck-suppress unusedStructMember
    int map_size_y;                // cppcheck-suppress unusedStructMember
    std::vector<BlockDTO> blocks;  // cppcheck-suppress unusedStructMember

    uint8_t cantidadjugadores;  // No hace falta? El dto match lo dira

    GameContext():
            id_lobby(0),
            dualplay(true),
            first_player(1),
            second_player(2),
            map_size_x(50),
            map_size_y(20),
            cantidadjugadores(4) {}
};

#endif
