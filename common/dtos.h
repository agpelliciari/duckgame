#ifndef LIB_DTOS_H
#define LIB_DTOS_H

#include <cstdint>
#include <string>

enum LobbyAction:uint8_t { 
NEW_LOBBY = 0x16, 
JOIN_LOBBY = 0x17, 
START_LOBBY = 0x18
};

#endif
