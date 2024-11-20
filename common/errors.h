#ifndef LIB_ERRORS_H
#define LIB_ERRORS_H

#include <cstdint>

enum LobbyErrorType : uint8_t {
    UNKNOWN = 1,
    SERVER_ERROR = 2,  // For internal errors on server... or shutdowns of it, 'q'
    ANFITRION_LEFT = 3,
    LOBBY_NOT_FOUND = 4,
    LOBBY_ALREADY_STARTED = 5,
    LOBBY_NO_SPACE = 6,
    MAP_INVALID = 7
};

#endif
