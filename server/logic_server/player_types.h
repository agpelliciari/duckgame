
#ifndef PLAYER_TYPES_H
#define PLAYER_TYPES_H

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

enum class TypeMoveAction {
    NONE,
    MOVE_LEFT,
    MOVE_RIGHT,
    STAY_DOWN,
    JUMP,
    FLAP
};

#endif //PLAYER_TYPES_H
