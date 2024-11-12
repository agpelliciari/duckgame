#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <cstdint>
#include <string>
#include <vector>

#include "common/dtosmap.h"

struct MapObject {
    int row;
    int column;
    int zIndex;
    const std::string& texture;
};

struct GameContext {
    unsigned int id_lobby;  // cppcheck-suppress unusedStructMember

    bool started;

    bool dualplay;          // cppcheck-suppress unusedStructMember
    uint8_t first_player;   // cppcheck-suppress unusedStructMember
    uint8_t second_player;  // cppcheck-suppress unusedStructMember


    std::string map_background;    // cppcheck-suppress unusedStructMember
    int map_width;                 // cppcheck-suppress unusedStructMember
    int map_height;                // cppcheck-suppress unusedStructMember
    std::vector<BlockDTO> blocks;  // cppcheck-suppress unusedStructMember

    uint8_t cantidadjugadores;  // No hace falta? El dto match lo dira

    GameContext():
            id_lobby(0),
            started(false),
            dualplay(true),
            first_player(1),
            second_player(2),
            map_width(50),
            map_height(20),
            cantidadjugadores(4) {}
};

#endif
