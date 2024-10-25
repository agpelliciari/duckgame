#ifndef CLIENT_ANIMATION_H_
#define CLIENT_ANIMATION_H_

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

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
    float positionX;  // cppcheck-suppress unusedStructMember

    float positionY;  // cppcheck-suppress unusedStructMember

    float speedX;  // cppcheck-suppress unusedStructMember

    float speedY;  // cppcheck-suppress unusedStructMember

    // Drawing flags

    int spriteX;  // cppcheck-suppress unusedStructMember

    int spriteY;  // cppcheck-suppress unusedStructMember

    unsigned int frameTicks;  // cppcheck-suppress unusedStructMember

    int runPhase;  // cppcheck-suppress unusedStructMember

    // Movement flags

    bool moveRight;  // cppcheck-suppress unusedStructMember

    bool moveLeft;  // cppcheck-suppress unusedStructMember

    bool facingLeft;  // cppcheck-suppress unusedStructMember

    bool onGround;  // cppcheck-suppress unusedStructMember

    bool layingDown;  // cppcheck-suppress unusedStructMember

    bool spacePressed;  // cppcheck-suppress unusedStructMember

    bool flying;  // cppcheck-suppress unusedStructMember

public:
    Animation();

    // Timing: calculate difference between this and previous frame in
    // milliseconds
    void updateFrame();

    // Update game state for this frame
    void updatePosition();

    // Set sprite coordinates based on the character's state
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

#endif  // CLIENT_ANIMATION_H_
