#include "animation.h"

#include <iostream>

Animation::Animation(const GameContext& context): animationBuilders(), frameTicks(0) {
    for (int i = 1; i <= static_cast<int>(context.cantidadjugadores); i++) {
        animationBuilders.emplace(i, AnimationBuilder());
    }
}

void Animation::updateFrame() { frameTicks = SDL_GetTicks(); }

void Animation::updateSprite(const MatchDto& matchDto) {
    for (const PlayerDTO& player: matchDto.players) {
        AnimationBuilder* builder = getAnimationBuilder(player.id);
        if (builder) {
            updatePlayerAnimation(*builder, player);
        }
    }
}

AnimationBuilder* Animation::getAnimationBuilder(int playerId) {
    auto it = animationBuilders.find(playerId);
    if (it != animationBuilders.end()) {
        return &it->second;
    }
    return nullptr;
}

void Animation::updatePlayerAnimation(AnimationBuilder& builder, const PlayerDTO& player) {
    switch (player.move_action) {
        case TypeMoveAction::MOVE_RIGHT:
            builder.facingLeft = false;
            builder.spriteX =
                    STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / RUNNING_ANIMATION_SPEED) %
                                                       RUNNING_ANIMATION_FRAMES);
            builder.spriteY = STARTING_SPRITE_Y;
            break;
        case TypeMoveAction::MOVE_LEFT:
            builder.facingLeft = true;
            builder.spriteX =
                    STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / RUNNING_ANIMATION_SPEED) %
                                                       RUNNING_ANIMATION_FRAMES);
            builder.spriteY = STARTING_SPRITE_Y;
            break;
        case TypeMoveAction::JUMP:
            builder.spriteX =
                    STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / JUMPING_ANIMATION_SPEED) %
                                                       JUMPING_ANIMATION_FRAMES);
            builder.spriteY = JUMPING_SPRITE_Y;
            break;
        case TypeMoveAction::FLAP:
            builder.spriteX = STARTING_SPRITE_X + SPRITE_SIZE * FLAPPING_SPRITE_X_OFFSET;
            builder.spriteY = FLAPPING_SPRITE_Y;
            break;
        case TypeMoveAction::STAY_DOWN:
            builder.spriteX = STARTING_SPRITE_X;
            builder.spriteY = LAY_DOWN_SPRITE_Y;
            break;
        case TypeMoveAction::NONE:
            builder.spriteX = STARTING_SPRITE_X;
            builder.spriteY = STARTING_SPRITE_Y;
            break;
    }
}

bool Animation::isFacingLeft(int playerId) {
    AnimationBuilder* builder = getAnimationBuilder(playerId);
    if (builder) {
        return builder->facingLeft;
    }
    return false;
}

int Animation::getSpriteX(int playerId) {
    AnimationBuilder* builder = getAnimationBuilder(playerId);
    if (builder) {
        return builder->spriteX;
    }
    return 0;
}

int Animation::getSpriteY(int playerId) {
    AnimationBuilder* builder = getAnimationBuilder(playerId);
    if (builder) {
        return builder->spriteY;
    }
    return 0;
}

Animation::~Animation() = default;
