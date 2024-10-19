#ifndef LIB_DTOS_H
#define LIB_DTOS_H

#include <cstdint>
#include <sstream>
#include <string>

enum LobbyActionType : uint8_t {
    NEW_LOBBY = 0x16,
    JOIN_LOBBY = 0x17,
    STARTED_LOBBY = 0x18,
    // CANCELED_LOBBY = 0x19
};

struct lobby_action {
    LobbyActionType action;
    uint8_t attached_id;  // Podria ser el del lobby o uno para seleccionar el mapa.
} __attribute__((packed));


enum PlayerActionType : uint8_t {
    PICK_UP = 3,
};

struct player_action_dto {
    PlayerActionType type;
    uint8_t playerind;
    uint8_t specific_info;
} __attribute__((packed));


// Necesitamos el dto del estado ya que ese es el que reciben los notifiers!
// Osea la queue del notifier es de estados de partida/ snapshots
// Igual podemos crear la clase, y que sea solo el duckdto o asi
// O bueno nose ja a veces es mejor ir de lo mas general !
// Solo falta el tema del estado de partida si, tipo iniciada, terminada , cancelada. Y el nro de
// ronda claro, o
struct coordinates_dto {
    int x;
    int y;
} __attribute__((packed));

enum WeaponType : uint8_t {
    BAZOOKA_W = 0x01,
};

struct weapon_dto {
    WeaponType tipo;
} __attribute__((packed));

struct armor_dto {
    uint8_t equipped;
} __attribute__((packed));


struct duck_dto {
    int id;
    bool is_alive;
    coordinates_dto coordinates;
    weapon_dto weapon;
    armor_dto helmet;
    armor_dto chest_armor;
} __attribute__((packed));


enum MatchStateType : uint8_t {
    INICIADA = 0x01,
    TERMINADA = 0x02,
    CANCELADA = 0x03,
};

struct match_info_dto {
    MatchStateType estado;
    uint8_t numronda;
};

class MatchDto {
public:
    match_info_dto info;

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

//

#endif
