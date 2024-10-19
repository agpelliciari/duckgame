#ifndef LIB_DTOS_PLAYER_H
#define LIB_DTOS_PLAYER_H

#include <cstdint>

enum PlayerActionType : uint8_t {
    PICK_UP = 3,
};

struct PlayerActionDTO {
    PlayerActionType type;
    uint8_t playerind;
    uint8_t specific_info;
} __attribute__((packed));


enum class TypeWeapon {
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

enum class TypeMoveAction { NONE, MOVE_LEFT, MOVE_RIGHT, STAY_DOWN, JUMP, FLAP };

struct PlayerDTO {
    int id;
    bool is_alive;
    int coord_x;
    int coord_y;
    TypeWeapon weapon;
    bool helmet;
    bool chest_armor;
    TypeMoveAction move_action;

    PlayerDTO(int id_, bool alive, int x, int y, TypeWeapon w, bool h, bool armor,
              TypeMoveAction action):
            id(id_),
            is_alive(alive),
            coord_x(x),
            coord_y(y),
            weapon(w),
            helmet(h),
            chest_armor(armor),
            move_action(action) {}

};  //__attribute__((packed));

#endif
