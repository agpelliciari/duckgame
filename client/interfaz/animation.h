#ifndef CLIENT_ANIMATION_H_
#define CLIENT_ANIMATION_H_

#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/gamecontext.h"
#include "common/dtosgame.h"

#include "animation_builder.h"
#include "sound_manager.h"

class Animation {
private:
    std::unordered_map<int, AnimationBuilder>
            animationBuilders;  // cppcheck-suppress unusedStructMember
    
    std::vector<BombExplosion> explosions;

    unsigned int frameTicks;  // cppcheck-suppress unusedStructMember

    unsigned int lastUpdateTicks;

    AnimationBuilder* getAnimationBuilder(int playerId);

    void updatePlayerAnimation(AnimationBuilder& builder, const PlayerDTO& player);

    void updateDoingActionAnimation(AnimationBuilder& builder, const PlayerDTO& player, const TypeDoingAction& action);

    void setBuilder(AnimationBuilder& builder, int spriteX, int spriteY, bool facingLeft);

    void setBuilder(AnimationBuilder& builder, int spriteX, int spriteY);

    // Timing: calculate difference between this and previous frame in
    // milliseconds
    void updateFrame();

    float updateDeltaTime();

    void updateExplosionsVector(AnimationBuilder& builder, float deltaTime);

    void updateGameEvents(const MatchDto& matchDto);

    void updateBombExplosions(float deltaTime);

public:
    Animation(const GameContext& context);

    // Set sprite coordinates based on the character's state
    void update(const MatchDto& matchDto);

    bool isFacingLeft(int playerId);

    int getSpriteX(int playerId);

    int getSpriteY(int playerId);

    std::vector<ExplosionAnimation>& getExplosions(int playerId);

    std::vector<BombExplosion> getBombExplosions();

    float getIndicatorSprite(float width);

    ~Animation();
};

#endif  // CLIENT_ANIMATION_H_
