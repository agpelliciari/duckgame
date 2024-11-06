#ifndef LIB_DTOS_H
#define LIB_DTOS_H

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include "./dtosobject.h"
#include "./dtosplayer.h"


enum ProjectileType : uint8_t {
    GRANADA,
    BANANA,
    PEW_PEW_LASER,
    LASER_RIFLE,
    AK_47,
    PISTOLA_DE_DUELOS,
    PISTOLA_COWBOY,
    MAGNUM,
    ESCOPETA,
    SNIPER,
    BURST
};

struct ProjectileDTO {
    struct MapPoint pos;       // cppcheck-suppress unusedStructMember
    enum ProjectileType tipo;  // cppcheck-suppress unusedStructMember
};

struct DynamicObjDTO {
    struct MapPoint pos;
    TypeDynamicObject type;
    DynamicObjDTO(coordinate_t x, coordinate_t y, TypeDynamicObject _type):
            pos(x, y), type(_type) {}
    DynamicObjDTO() {}
};


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
    std::vector<PlayerDTO> players;      // cppcheck-suppress unusedStructMember
    std::vector<DynamicObjDTO> objects;  // cppcheck-suppress unusedStructMember

    explicit MatchDto(MatchStateType _estado, uint8_t _numronda): info({_estado, _numronda}) {}
    explicit MatchDto(match_info_dto _info): info(_info) {}
    MatchDto(): info({INICIADA, 0}) {}


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

struct PlayerStatDto {
    uint8_t id;    // cppcheck-suppress unusedStructMember
    uint8_t wins;  // cppcheck-suppress unusedStructMember
};

// Info estadisticas
class StatInfoDto {
public:
    MatchStateType estado;
    uint8_t numronda;
    std::vector<PlayerStatDto> stats;  // cppcheck-suppress unusedStructMember

    explicit StatInfoDto(MatchStateType _estado, uint8_t _numronda):
            estado(_estado), numronda(_numronda) {}
};


#endif
