#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#define NOT_DEFINED_FLAG -1
#include <vector>

#include "common/dtosobject.h"

struct GameContext {
    unsigned int id_lobby;  // cppcheck-suppress unusedStructMember

    int first_player;   // cppcheck-suppress unusedStructMember
    int second_player;  // cppcheck-suppress unusedStructMember

    int map_size_x;                // cppcheck-suppress unusedStructMember
    int map_size_y;                // cppcheck-suppress unusedStructMember
    std::vector<BlockDTO> blocks;  // cppcheck-suppress unusedStructMember

    // uint8_t cantidadjugadores; // No hace falta? El dto match lo dira
    GameContext():
            id_lobby(0),
            first_player(NOT_DEFINED_FLAG),
            second_player(NOT_DEFINED_FLAG),
            map_size_x(50),
            map_size_y(20) {}
};

#endif
