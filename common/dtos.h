#ifndef LIB_DTOS_H
#define LIB_DTOS_H

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include "./dtosplayer.h"

enum LobbyActionType : uint8_t {
    // Tipos acciones para unirse/salir ademas
    CREATE_LOBBY = 0x16,
    JOIN_LOBBY = 0x17,
    LEAVE_LOBBY = 0x20,
    // Para empezar/cancelar
    STARTED_LOBBY = 0x18,
    CANCEL_LOBBY = 0x19
    // Tipos de acciones de configuracion?
};

struct lobby_info {
    LobbyActionType action;
    uint8_t attached_id;  // Podria ser el del lobby o uno para seleccionar el mapa.
} __attribute__((packed));

struct lobby_action {
    LobbyActionType type;
    uint8_t info;  // Podria ser el del lobby o uno para seleccionar el mapa.
} __attribute__((packed));


enum MatchStateType : uint8_t {
    INICIADA = 0x01,
    TERMINADA = 0x02,
    CANCELADA = 0x03,
};

struct match_info_dto {
    MatchStateType estado;
    uint8_t numronda;
    // uint8_t cantidadjugadores;
};

class MatchDto {
public:
    match_info_dto info;
    std::vector<PlayerDTO> players;  // cppcheck-suppress unusedStructMember

    explicit MatchDto(MatchStateType _estado, uint8_t _numronda): info({_estado, _numronda}) {}
    explicit MatchDto(match_info_dto _info): info(_info) {}


    std::string parse() const {
        std::stringstream result;
        if (info.estado == INICIADA) {
            result << "INICIADA ";
        } else if (info.estado == TERMINADA) {
            result << "TERMINADA ";

        } else if (info.estado == CANCELADA) {
            result << "CANCELADA ";
        }
        result << (int)info.numronda;
        return result.str();
    }
};

#endif
