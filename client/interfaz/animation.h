#ifndef CLIENT_ANIMATION_H_
#define CLIENT_ANIMATION_H_

#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/gamecontext.h"
#include "common/dtosgame.h"

#include "sound_manager.h"

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

#define INDICATOR_ANIMATION_FRAMES 5
#define INDICATOR_ANIMATION_SPEED 150


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

    SoundManager& soundManager;

    unsigned int frameTicks;  // cppcheck-suppress unusedStructMember

    AnimationBuilder* getAnimationBuilder(int playerId);

    void updatePlayerAnimation(AnimationBuilder& builder, const PlayerDTO& player);

    void setBuilder(AnimationBuilder& builder, int spriteX, int spriteY, bool facingLeft);

    void setBuilder(AnimationBuilder& builder, int spriteX, int spriteY);

public:
    Animation(const GameContext& context, SoundManager& soundManager);

    // Timing: calculate difference between this and previous frame in
    // milliseconds
    void updateFrame();

    // Set sprite coordinates based on the character's state
    void updateSprite(const MatchDto& matchDto);

    bool isFacingLeft(int playerId);

    int getSpriteX(int playerId);

    int getSpriteY(int playerId);

    float getIndicatorSprite(float width);

    ~Animation();
};

#endif  // CLIENT_ANIMATION_H_
