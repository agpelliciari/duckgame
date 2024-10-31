#ifndef CLIENT_ANIMATION_H_
#define CLIENT_ANIMATION_H_

#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/gamecontext.h"
#include "common/dtos.h"
#include "common/dtosplayer.h"

// also used in UILoop
#define SCREEN_WIDTH 640
#define GROUND 400

#define INITIAL_POSITION_X 100.0
#define INITIAL_POSITION_Y 400.0
#define INITIAL_SPEED_X 4.0
#define INITIAL_SPEED_Y 0.0
#define GRAVITY 0.5

#define SPRITE_SIZE 32

#define RUNNING_ANIMATION_FRAMES 6
#define RUNNING_ANIMATION_SPEED 90
#define JUMPING_ANIMATION_FRAMES 5
#define JUMPING_ANIMATION_SPEED 300

#define STARTING_SPRITE_X 1
#define STARTING_SPRITE_Y 10

#define JUMPING_SPRITE_Y 41

#define LAY_DOWN_SPRITE_Y 72

#define FLAPPING_SPRITE_X_OFFSET 2
#define FLAPPING_SPRITE_Y 72


struct AnimationBuilder {
    int spriteX;  // cppcheck-suppress unusedStructMember

    int spriteY;  // cppcheck-suppress unusedStructMember

    bool facingLeft;  // cppcheck-suppress unusedStructMember

    AnimationBuilder() {
        spriteX = STARTING_SPRITE_X;

        spriteY = STARTING_SPRITE_Y;

        facingLeft = false;
    }
};

class Animation {
private:
    // Drawing flags
    std::unordered_map<int, AnimationBuilder>
            animationBuilders;  // cppcheck-suppress unusedStructMember

    unsigned int frameTicks;  // cppcheck-suppress unusedStructMember
public:
    explicit Animation(const GameContext& context);

    // Timing: calculate difference between this and previous frame in
    // milliseconds
    void updateFrame();

    // Update game state for this frame
    // void updatePosition();

    // Set sprite coordinates based on the character's state
    void updateSprite(MatchDto& matchDto);

    /*void rightCommandFlags();

    void stopRightCommand();

    void leftCommandFlags();

    void stopLeftCommand();

    void downCommandFlags();

    void stopDownCommand();

    void spaceCommandFlags();

    void stopSpaceCommand();

    float getPositionX() const;

    float getPositionY() const;*/

    bool isFacingLeft(int playerId) const;

    int getSpriteX(int playerId) const;

    int getSpriteY(int playerId) const;

    ~Animation();
};

#endif  // CLIENT_ANIMATION_H_
