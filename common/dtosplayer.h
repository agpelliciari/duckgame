#ifndef LIB_DTOS_PLAYER_H
#define LIB_DTOS_PLAYER_H

#include <cstdint>
#include <vector>
#include "./dtosobject.h"

typedef unsigned int player_id;


enum PlayerActionType : uint8_t {
    NONE = 0,
    MOVE_LEFT = 1,
    MOVE_LEFT_END = 2,
    MOVE_RIGHT = 3,
    MOVE_RIGHT_END = 4,
    STAY_DOWN = 5,
    JUMP = 6,
    FLAPPING_END = 7,
    STAY_DOWN_START = 8,
    STAY_DOWN_END = 9,
    AIM_UP_START = 10,
    AIM_UP_END = 11,
    SHOOT = 12,
    PICK_UP_ITEM = 13,
    DROP_ITEM = 14
};

struct PlayerActionDTO {
    PlayerActionType type;
    uint8_t playerind;
    //uint8_t specific_info;

    PlayerActionDTO(const PlayerActionType& _type, uint8_t _playerind):
            type(_type), playerind(_playerind){}//, specific_info(0) {}
    //PlayerActionDTO(const PlayerActionType& _type, uint8_t _playerind, uint8_t _info):
    //        type(_type), playerind(_playerind){}//, specific_info(_info) {}
    PlayerActionDTO(): type(NONE), playerind(0){}//, specific_info(0) {}
} __attribute__((packed));


enum class TypeWeapon : uint8_t {
    NONE,
    GRANADA,
    BANANA,
    PEW_PEW_LASER,
    LASER_RIFLE,
    AK_47,
    PISTOLA_DE_DUELOS,
    PISTOLA_COWBOY,
    MAGNUM,
    ESCOPETA,
    SNIPER
};

enum class TypeMoveAction : uint8_t {
    NONE,
    MOVE_LEFT,
    MOVE_RIGHT,
    STAY_DOWN,
    AIR_NEUTRAL,
    AIR_LEFT,
    AIR_RIGHT,
    FLAP_NEUTRAL,
    FLAP_LEFT,
    FLAP_RIGHT
};

enum class TypeDoingAction : uint8_t {
    NONE,
    SHOOTING,
    SHOOTING_UP,
    DAMAGED,
    PICK_UP
};  // Capaz podria estar aca el flapping?

struct PlayerDTO {
    int id;
    struct MapPoint pos;
    bool is_alive;
    
    TypeWeapon weapon;
    
    TypeMoveAction move_action;
    TypeDoingAction doing_action;

    bool helmet;
    bool chest_armor;
    bool aiming_up;

    uint8_t hp;
    uint8_t munition;

    PlayerDTO(int id_, bool alive, int x, int y, TypeWeapon w, bool h, bool armor,
              TypeMoveAction action):
            id(id_),
            pos(x, y),
            is_alive(alive),
            weapon(w),
            move_action(action),
            doing_action(TypeDoingAction::NONE),
            helmet(h),
            chest_armor(armor),
            aiming_up(false),
            hp(0),
            munition(0)
            {}

    PlayerDTO(int id_, bool alive, int x, int y, TypeMoveAction state):
            id(id_),
            pos(x, y),
            is_alive(alive),
            weapon(TypeWeapon::NONE),
            move_action(state),
            doing_action(TypeDoingAction::NONE),
            helmet(false),
            chest_armor(false),
            aiming_up(false),
            hp(alive?1:0),
            munition(0)
            {}
    PlayerDTO(): PlayerDTO(0, false, 0, 0, TypeMoveAction::NONE) {}
};

#endif
