#include "animation.h"

Animation::Animation() : 
    positionX(INITIAL_POSITION_X),
    positionY(INITIAL_POSITION_Y),
    speedX(INITIAL_SPEED_X),
    speedY(INITIAL_SPEED_Y),
    spriteX(1),
    spriteY(10),
    frameTicks(0), 
    runPhase(0),
    moveRight(false),
    moveLeft(false),
    facingLeft(false),
    onGround(true),
    layingDown(false),
    spacePressed(false),
    flying(false) {}

void Animation::updateFrame() {
    frameTicks = SDL_GetTicks();
}

void Animation::updatePosition() {
    if (!layingDown) {
        // Apply gravity
        if (flying) {
            speedY += GRAVITY * 0.5; // Reduced gravity effect when flying
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
}

void Animation::updateSprite() {
    // Set sprite coordinates based on the character's state
    if (layingDown) {
        spriteY = 72; // Laying down sprite row
        spriteX = 1;  // Assuming a single frame for laying down
    } else if (onGround) {
        spriteY = 10; // Standing or running sprite row
        if (moveRight || moveLeft) {
            spriteX = 1 + 32 * runPhase; // Running animation
        } else {
            spriteX = 1; // Standing still
        }
    } else {
        if (flying) {
            spriteY = 72; // flying sprite row
            spriteX = 1 + 32 *2;  // Assuming a single frame for flying
        } else {
            spriteY = 41; // Jumping sprite row
            spriteX = 1 + 32 * runPhase; // Assuming a single frame for jumping
        }
    }
}

void Animation::rightCommandFlags() {
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
    if (onGround) { // Only allow laying down if on the ground
        layingDown = true;
    }
}

void Animation::stopDownCommand() { layingDown = false; }

void Animation::spaceCommandFlags() {
    if (onGround) { // StartJump()
        speedY = -12.0;
        onGround = false;
        spriteX = 1; // Reset spriteX to start the jump animation
    } else if (!spacePressed) { // Reduce gravity effect if jump button is pressed again while in the air
        speedY -= GRAVITY * 0.5;
        flying = true;
    }
    spacePressed = true;
}

void Animation::stopSpaceCommand() {
    spacePressed = false;
    if (speedY < -6.0) { // EndJump()
        speedY = -6.0;
    }
}

float Animation::getPositionX() const { return positionX; }

float Animation::getPositionY() const { return positionY; }

bool Animation::isFacingLeft() const { return facingLeft; }

int Animation::getSpriteX() const { return spriteX; }

int Animation::getSpriteY() const { return spriteY; }

Animation::~Animation() = default;
