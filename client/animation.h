#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

enum AnimationState {
    STATE_STANDING,
    STATE_RUNNING_RIGHT,
    STATE_RUNNING_LEFT,
};
// also used in UILoop
#define SCREEN_WIDTH 640
#define GROUND 400

#define INITIAL_POSITION_X 100.0
#define INITIAL_POSITION_Y 400.0
#define INITIAL_SPEED_X 4.0
#define INITIAL_SPEED_Y 0.0
#define GRAVITY 0.5

class Animation {
private:
    // Timing variables

    float positionX;

    float positionY;

    float speedX;

    float speedY;

    // Drawing flags

    int spriteX;

    int spriteY;

    unsigned int frameTicks;

    int runPhase;

    // Movement flags

    bool moveRight;

    bool moveLeft;

    bool facingLeft;

    bool onGround;

    bool layingDown;

    bool spacePressed;

    bool flying;
public:
    Animation();

    // Timing: calculate difference between this and previous frame in milliseconds
    void updateFrame();

    // Update game state for this frame
    void updatePosition();

    // Pick sprite from sprite atlas based on whether player is running and run animation phase
    void updateSprite();

    void rightCommandFlags();

    void stopRightCommand();

    void leftCommandFlags();

    void stopLeftCommand();

    void downCommandFlags();

    void stopDownCommand();

    void spaceCommandFlags();

    void stopSpaceCommand();

    float getPositionX() const;

    float getPositionY() const;

    bool isFacingLeft() const;

    int getSpriteX() const;

    int getSpriteY() const;

    ~Animation();
};

#endif
