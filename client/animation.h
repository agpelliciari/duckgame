#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

enum AnimationState {
    STATE_STANDING,
    STATE_RUNNING_RIGHT,
    STATE_RUNNING_LEFT,
};

class Animation {
private:
    unsigned int prevTicks;

    unsigned int frameTicks;

    unsigned int frameDelta;

    int runPhase;

    float position;

    bool facingLeft;

    AnimationState state;

    int spriteX;

    int spriteY;
public:
    Animation();

    // Timing: calculate difference between this and previous frame in milliseconds
    void updateFrame();

    // Update game state for this frame
    void updatePosition();

    // Pick sprite from sprite atlas based on whether player is running and run animation phase
    void updateSprite();

    unsigned int getFrameDelta() const;

    unsigned int getFrameTicks() const;

    float getPosition() const;

    void setPosition(float newPosition);

    void setState(AnimationState newState);

    void flip(bool flip);

    bool isFacingLeft() const;

    int getSpriteX() const;

    int getSpriteY() const;

    ~Animation();
};

#endif
