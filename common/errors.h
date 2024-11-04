#ifndef LIB_ERRORS_H
#define LIB_ERRORS_H

#include <cstdint>

enum LobbyErrorType : uint8_t {
    UNKNOWN = 0,
    SERVER_ERROR = 1,  // For internal errors on server... or shutdowns of it
    ANFITRION_LEFT = 2,
    LOBBY_NOT_FOUND = 3,
    LOBBY_ALREADY_STARTED = 4,
    LOBBY_NO_SPACE = 5
};

#endif
