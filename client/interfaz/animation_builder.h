#ifndef ANIMATION_DTOS_H_
#define ANIMATION_DTOS_H_

#include <string>
#include <vector>

#define SPRITE_SIZE 32

#define RUNNING_ANIMATION_FRAMES 6
#define RUNNING_ANIMATION_SPEED 90

#define JUMPING_ANIMATION_FRAMES 5
#define JUMPING_ANIMATION_SPEED 600

#define STARTING_SPRITE_X 0
#define STARTING_SPRITE_Y 0

#define JUMPING_SPRITE_Y 32

#define LAY_DOWN_SPRITE_Y 64

#define FLAPPING_SPRITE_X_OFFSET 2
#define FLAPPING_SPRITE_Y 64

#define INDICATOR_ANIMATION_FRAMES 5
#define INDICATOR_ANIMATION_SPEED 150

#include "explosion_animation.h"

struct AnimationBuilder {
    int spriteX;  // cppcheck-suppress unusedStructMember
    int spriteY;  // cppcheck-suppress unusedStructMember
    bool facingLeft;  // cppcheck-suppress unusedStructMember
    std::vector<ExplosionAnimation> explosions;  // cppcheck-suppress unusedStructMember

    AnimationBuilder() {
        spriteX = STARTING_SPRITE_X;
        spriteY = STARTING_SPRITE_Y;
        facingLeft = false;
    }

    void addExplosion(const std::string& texture, int size, float duration, int frames) {
        explosions.emplace_back(texture, size, duration, frames);
    }
};

#endif
