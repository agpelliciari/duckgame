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



class MatchDto {
public:
    //match_info_dto info;
    std::vector<PlayerDTO> players;      // cppcheck-suppress unusedStructMember
    std::vector<DynamicObjDTO> objects;  // cppcheck-suppress unusedStructMember
    
    MatchDto(){}
    //explicit MatchDto(MatchStateType _estado, uint8_t _numronda): info({_estado, _numronda}) {}
    //explicit MatchDto(match_info_dto _info): info(_info) {}
    //MatchDto(): info({INICIADA, 0}) {}

    const PlayerDTO* getPlayer(const int id) const {
        for (const PlayerDTO& player: players) {
            // cppcheck-suppress useStlAlgorithm
            if (player.id == id) {
                return &player;
            }
        }

        return NULL;
    }

    std::string parse() const {
        std::stringstream result;
        result << "player count" << players.size();
        return result.str();
    }
};

struct PlayerStatDto {
    uint8_t id;    // cppcheck-suppress unusedStructMember
    uint8_t wins;  // cppcheck-suppress unusedStructMember
};

enum MatchStateType : uint8_t {
    INICIADA = 0x01,
    PAUSADA = 0x04,
    ROUND_END = 0x05,
    TERMINADA = 0x02,
    CANCELADA = 0x03,
};

// Info estadisticas
class MatchStatsInfo {
public:
    MatchStateType state;
    uint8_t numronda;
    std::vector<PlayerStatDto> stats;  // cppcheck-suppress unusedStructMember
    uint8_t champion_player; // cppcheck-suppress unusedStructMember

    explicit MatchStatsInfo(MatchStateType _estado, uint8_t _numronda, const uint8_t _champion_player):
            state(_estado), numronda(_numronda),champion_player(_champion_player) {}
            
    MatchStatsInfo():state(PAUSADA), numronda(1),champion_player(0) {}
    
    std::string parse() const{
        std::stringstream result;
        result << (int)numronda;
        if (state == INICIADA) {
            result << " INICIADA ";
        } else if (state == TERMINADA) {
            result << " TERMINADA WON "<< (int) champion_player;
        } else if (state == PAUSADA) {
            result << " ROUND END :: WON "<< (int) champion_player;
        } else if (state == CANCELADA) {
            result << " CANCELADA ";
        }
        return result.str();    
    }
};


#endif
