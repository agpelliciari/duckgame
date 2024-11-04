#ifndef LIB_DTOS_PLAYER_H
#define LIB_DTOS_PLAYER_H

#include <cstdint>

enum PlayerActionType : uint8_t {
    NONE = 0,
    MOVE_LEFT = 1,
    MOVE_RIGHT = 2,
    STAY_DOWN = 3,
    JUMP = 4,
    PICK_UP = 5,
};

struct PlayerActionDTO {
    PlayerActionType type;
    uint8_t playerind;
    uint8_t specific_info;

    PlayerActionDTO(const PlayerActionType& _type, uint8_t _playerind):
            type(_type), playerind(_playerind), specific_info(0) {}
    PlayerActionDTO(const PlayerActionType& _type, uint8_t _playerind, uint8_t _info):
            type(_type), playerind(_playerind), specific_info(_info) {}
    PlayerActionDTO(): type(NONE), playerind(0), specific_info(0) {}
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

enum class TypeMoveAction : uint8_t { NONE, MOVE_LEFT, MOVE_RIGHT, STAY_DOWN, JUMP, FLAP };

enum class TypeDoingAction : uint8_t {
    NOTHING,
    SHOOTING,
    PICK_UP,
    //FLAPPING //el flapping no hace falta
};  // Capaz podria estar aca el flapping?

struct PlayerDTO {
    int id;
    int coord_x;
    int coord_y;
    bool is_alive;
    TypeWeapon weapon;
    TypeMoveAction move_action;
    TypeDoingAction doing_action;

    bool helmet;
    bool chest_armor;
    bool aiming_up;

    PlayerDTO(int id_, bool alive, int x, int y, TypeWeapon w, bool h, bool armor,
              TypeMoveAction action):
            id(id_),
            coord_x(x),
            coord_y(y),
            is_alive(alive),
            weapon(w),
            move_action(action),
            doing_action(TypeDoingAction::NOTHING),
            helmet(h),
            chest_armor(armor),
            aiming_up(false) {}

    PlayerDTO(int id_, bool alive, int x, int y, TypeMoveAction state):
            id(id_),
            coord_x(x),
            coord_y(y),
            is_alive(alive),
            weapon(TypeWeapon::NONE),
            move_action(state),
            doing_action(TypeDoingAction::NOTHING),
            helmet(false),
            chest_armor(false),
            aiming_up(false) {}

    PlayerDTO() {}  // Para read.
};                  //__attribute__((packed));

#endif
