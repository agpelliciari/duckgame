#include "animation.h"

Animation::Animation() : 
    prevTicks(SDL_GetTicks()), 
    frameTicks(0), 
    frameDelta(0),
    runPhase(0),
    position(0.0),
    facingLeft(false),
    state(STATE_STANDING),
    spriteX(1),
    spriteY(10) {}

void Animation::updateFrame() {
    frameTicks = SDL_GetTicks();
	frameDelta = frameTicks - prevTicks;
	prevTicks = frameTicks;
}

void Animation::updatePosition() {
    if (state == STATE_RUNNING_RIGHT) {
        position += frameDelta * 0.2;
        runPhase = (frameTicks / 100) % 6;
    } else if (state == STATE_RUNNING_LEFT) {
        position -= frameDelta * 0.2;
        runPhase = (frameTicks / 100) % 6;
    } else {
        runPhase = 0;
    }
}

void Animation::updateSprite() {
    spriteX = 1;
    if (state == STATE_RUNNING_RIGHT || state == STATE_RUNNING_LEFT) {
        spriteX = 1 + 32 * runPhase;
        spriteY = 10;
    }
}

unsigned int Animation::getFrameDelta() const { return frameDelta; }

unsigned int Animation::getFrameTicks() const { return frameTicks; }

float Animation::getPosition() const { return position; }

void Animation::setPosition(float newPosition) { position = newPosition; }

void Animation::setState(AnimationState newState) { state = newState; }

void Animation::flip(bool flip) { facingLeft = flip; }

bool Animation::isFacingLeft() const { return facingLeft; }

int Animation::getSpriteX() const { return spriteX; }

int Animation::getSpriteY() const { return spriteY; }

Animation::~Animation() = default;
