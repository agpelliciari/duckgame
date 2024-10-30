#include "animation.h"

Animation::Animation(const GameContext& context): animationBuilders(), frameTicks(0) {
    for (int i = 1; i <= static_cast<int>(context.cantidadjugadores); i++) {
        animationBuilders.emplace(i, AnimationBuilder());
    }
}

void Animation::updateFrame() { frameTicks = SDL_GetTicks(); }

/*void Animation::updatePosition() {
    if (!layingDown) {
        // Apply gravity
        if (flying) {
            // Reduced gravity effect when flying
            speedY += GRAVITY * 0.5;
        } else {
            speedY += GRAVITY;
        }
        positionY += speedY;

        // Horizontal movement
        if (moveRight) {
            positionX += speedX;
            runPhase = (frameTicks / 100) % 6;
        }
        if (moveLeft) {
            positionX -= speedX;
            runPhase = (frameTicks / 100) % 6;
        }

        // Ground collision
        if (positionY >= GROUND) {
            positionY = GROUND;
            speedY = 0.0;
            onGround = true;
            flying = false;
        } else {
            onGround = false;
            runPhase = (frameTicks / 600) % 5;
        }

        // Screen wrapping
        if (positionX < 0) {
            positionX = SCREEN_WIDTH;
        }
        if (positionX > SCREEN_WIDTH) {
            positionX = 0;
        }
    }
}*/

void Animation::updateSprite(MatchDto& matchDto) {
    for (PlayerDTO& player: matchDto.players) {  // por cada jugador
        auto builder = animationBuilders.find(
                player.id);  // busco el id del jugador en mi dict de animaciones

        if (builder != animationBuilders.end()) {  // si lo encuentro
            switch (player.move_action) {
                case TypeMoveAction::MOVE_RIGHT:
                    builder->second.facingLeft = false;
                    builder->second.spriteX =
                            STARTING_SPRITE_X +
                            SPRITE_SIZE * ((frameTicks / RUNNING_ANIMATION_SPEED) %
                                           RUNNING_ANIMATION_FRAMES);
                    builder->second.spriteY = STARTING_SPRITE_Y;
                    break;
                case TypeMoveAction::MOVE_LEFT:
                    builder->second.facingLeft = true;
                    builder->second.spriteX =
                            STARTING_SPRITE_X +
                            SPRITE_SIZE * ((frameTicks / RUNNING_ANIMATION_SPEED) %
                                           RUNNING_ANIMATION_FRAMES);
                    builder->second.spriteY = STARTING_SPRITE_Y;
                    break;
                case TypeMoveAction::JUMP:
                    builder->second.spriteX =
                            STARTING_SPRITE_X +
                            SPRITE_SIZE * ((frameTicks / JUMPING_ANIMATION_SPEED) %
                                           JUMPING_ANIMATION_FRAMES);
                    builder->second.spriteY = JUMPING_SPRITE_Y;
                    break;
                case TypeMoveAction::FLAP:
                    builder->second.spriteX =
                            STARTING_SPRITE_X + SPRITE_SIZE * FLAPPING_SPRITE_X_OFFSET;
                    builder->second.spriteY = FLAPPING_SPRITE_Y;
                    break;
                case TypeMoveAction::STAY_DOWN:
                    builder->second.spriteX = STARTING_SPRITE_X;
                    builder->second.spriteY = LAY_DOWN_SPRITE_Y;
                    break;
                case TypeMoveAction::NONE:
                    builder->second.spriteX = STARTING_SPRITE_X;
                    builder->second.spriteY = STARTING_SPRITE_Y;
                    break;
            }
        }
    }
}

bool Animation::isFacingLeft(int playerId) const {
    auto builder = animationBuilders.find(playerId);
    if (builder != animationBuilders.end()) {
        return builder->second.facingLeft;
    }
    return false;
}

int Animation::getSpriteX(int playerId) const {
    auto builder = animationBuilders.find(playerId);
    if (builder != animationBuilders.end()) {
        return builder->second.spriteX;
    }
    return 0;
}

int Animation::getSpriteY(int playerId) const {
    auto builder = animationBuilders.find(playerId);
    if (builder != animationBuilders.end()) {
        return builder->second.spriteY;
    }
    return 0;
}

/*void Animation::rightCommandFlags() {
    moveRight = true;
    moveLeft = false;
    facingLeft = false;
}

void Animation::stopRightCommand() { moveRight = false; }

void Animation::leftCommandFlags() {
    moveLeft = true;
    moveRight = false;
    facingLeft = true;
}

void Animation::stopLeftCommand() { moveLeft = false; }

void Animation::downCommandFlags() {
    if (onGround) {
        layingDown = true;
    }
}

void Animation::stopDownCommand() { layingDown = false; }

void Animation::spaceCommandFlags() {
    if (onGround) {
        speedY = -12.0;
        onGround = false;
        spriteX = 1;
    } else if (!spacePressed) {
        speedY -= GRAVITY * 0.5;
        flying = true;
    }
    spacePressed = true;
}

void Animation::stopSpaceCommand() {
    spacePressed = false;
    if (speedY < -6.0) {
        speedY = -6.0;
    }
}

float Animation::getPositionX() const { return positionX; }

float Animation::getPositionY() const { return positionY; }*/

Animation::~Animation() = default;
