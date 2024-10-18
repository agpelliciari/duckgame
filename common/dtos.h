#ifndef LIB_DTOS_H
#define LIB_DTOS_H

#include <cstdint>
#include <string>

enum LobbyActionType:uint8_t { 
    NEW_LOBBY = 0x16, 
    JOIN_LOBBY = 0x17, 
    STARTED_LOBBY = 0x18,
    //CANCELED_LOBBY = 0x19
};



struct lobby_info {
    LobbyActionType lobby_action;
    uint8_t attached_id; // Podria ser el del lobby o uno para seleccionar el mapa. 
}  __attribute__((packed));


enum PlayerActionType:uint8_t { 
    PICK_UP = 3, 
};

struct player_action {
    uint8_t indice;
    PlayerActionType type;
}  __attribute__((packed));





#endif
