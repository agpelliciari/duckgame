#ifndef LIB_DTOS_LOBBY_H
#define LIB_DTOS_LOBBY_H

#include <cstdint>
#include <sstream>
#include <string>

#include "./errors.h"

enum LobbyActionType : uint8_t {
    // Accion inicial para saber la lobby.
    CREATE_LOBBY = 0x16,
    JOIN_LOBBY = 0x17,

    // player esta listo/ quiere empezar la partida. Player leave.. se fue.
    PLAYER_READY = 0x20,
    PLAYER_LEAVE = 0x22
};

enum LobbyResponseType : uint8_t {
    // Responses para acciones de lobby iniciales
    CREATED_LOBBY = 0x16,
    JOINED_LOBBY = 0x17,

    // Para empezar/cancelar/terminar la lobby.
    STARTED_LOBBY = 0x18,
    GAME_ERROR = 0x19,
    FINISHED_LOBBY = 0x21,

    // Notificaciones de cambios dentro de la lobby/configuracion
    PLAYER_NEW = 0x17,
    PLAYER_LEFT = 0x20,
    
    // For in-game lobby kind of..
    MATCH_PAUSE_TICK = 0x23,
    MATCH_PAUSE_END = 0x24
    
};

struct lobby_info {
    LobbyResponseType action;
    uint8_t data;  // Un numero. Que muchas veces es necesario

    lobby_info(LobbyResponseType _response, uint8_t num): action(_response), data(num) {}
    lobby_info(): action(GAME_ERROR), data(LobbyErrorType::UNKNOWN) {}
} __attribute__((packed));

struct lobby_action {
    LobbyActionType type;
    uint8_t info;  // Podria ser el del lobby o uno para seleccionar el mapa.
} __attribute__((packed));

#endif
