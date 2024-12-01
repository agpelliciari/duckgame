#include "animation.h"

Animation::Animation(const GameContext& context):
        animationBuilders(), frameTicks(0), lastUpdateTicks(0) {
    for (int i = 1; i <= static_cast<int>(context.cantidadjugadores); i++) {
        animationBuilders.emplace(i, AnimationBuilder());
    }
}

void Animation::updateFrame() { frameTicks = SDL_GetTicks(); }

float Animation::updateDeltaTime() {
    unsigned int currentTicks = SDL_GetTicks();
    float deltaTime = 0.0f;
    if (lastUpdateTicks > 0) {
        deltaTime = (currentTicks - lastUpdateTicks) / 1000.0f;
    }
    lastUpdateTicks = currentTicks;
    return deltaTime;
}

void Animation::updateExplosionsVector(AnimationBuilder& builder, float deltaTime) {
    for (ExplosionAnimation& explosion: builder.explosions) {
        explosion.update(deltaTime);
    }

    builder.explosions.erase(
        std::remove_if(builder.explosions.begin(), builder.explosions.end(), [](const ExplosionAnimation& explosion) { return explosion.isFinished(); }),
        builder.explosions.end()
    );
}

void Animation::updateGameEvents(const MatchDto& matchDto) {
    for (const GameEvent& event: matchDto.events) {
        if ((event.type == GameEventType::BOMB_EXPLOSION) || (event.type == GameEventType::GRENADE_EXPLOSION)) {
            std::cout << " guardando Explosion at " << event.pos.x << ", " << event.pos.y << std::endl;
            explosions.emplace_back(event.pos, "/weapons/explode.png", 64, 0.5f, 4);

        } //else if (event.type == GameEventType::BOX_DESTROYED) {}
    }
}

void Animation::updateBombExplosions(float deltaTime) {
    for (BombExplosion& explosion: explosions) {
        explosion.update(deltaTime);
    }

    explosions.erase(
        std::remove_if(explosions.begin(), explosions.end(), [](const BombExplosion& explosion) { return explosion.isFinished(); }),
        explosions.end()
    );
}

void Animation::update(const MatchDto& matchDto) {
    updateFrame();
    float deltaTime = updateDeltaTime();

    updateGameEvents(matchDto);
    updateBombExplosions(deltaTime);

    for (const PlayerDTO& player: matchDto.players) {
        AnimationBuilder* builder = getAnimationBuilder(player.id);
        if (builder) {
            if (player.is_alive) {
                updatePlayerAnimation(*builder, player);
                updateDoingActionAnimation(*builder, player, player.doing_action);
                updateExplosionsVector(*builder, deltaTime);
            } else {
                setBuilder(*builder, STARTING_SPRITE_X + SPRITE_SIZE, LAY_DOWN_SPRITE_Y);
            }
        }
    }
}

void Animation::updateDoingActionAnimation(AnimationBuilder& builder, const PlayerDTO& player, const TypeDoingAction& action) {
    if (action == TypeDoingAction::SHOOTING || action == TypeDoingAction::SHOOTING_UP) {
        if (player.weapon == TypeWeapon::PEW_PEW_LASER || player.weapon == TypeWeapon::LASER_RIFLE) {
            builder.addExplosion("/weapons/laserFlare.png", 16, 0.3f, 2);
        } else {
            if (player.weapon != TypeWeapon::GRANADA) {
                builder.addExplosion("/weapons/smallFlare.png", 11, 0.3f, 1);
            }
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

void Animation::setBuilder(AnimationBuilder& builder, int spriteX, int spriteY, bool facingLeft) {
    builder.spriteX = spriteX;
    builder.spriteY = spriteY;
    builder.facingLeft = facingLeft;
}

void Animation::setBuilder(AnimationBuilder& builder, int spriteX, int spriteY) {
    builder.spriteX = spriteX;
    builder.spriteY = spriteY;
}

void Animation::updatePlayerAnimation(AnimationBuilder& builder, const PlayerDTO& player) {
    switch (player.move_action) {
        case TypeMoveAction::MOVE_RIGHT:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / RUNNING_ANIMATION_SPEED) %
                                                           RUNNING_ANIMATION_FRAMES)),
                       STARTING_SPRITE_Y, false);
            break;
        case TypeMoveAction::MOVE_LEFT:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / RUNNING_ANIMATION_SPEED) %
                                                           RUNNING_ANIMATION_FRAMES)),
                       STARTING_SPRITE_Y, true);
            break;
        case TypeMoveAction::AIR_NEUTRAL:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / JUMPING_ANIMATION_SPEED) %
                                                           JUMPING_ANIMATION_FRAMES)),
                       JUMPING_SPRITE_Y);
            break;
        case TypeMoveAction::AIR_RIGHT:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / JUMPING_ANIMATION_SPEED) %
                                                           JUMPING_ANIMATION_FRAMES)),
                       JUMPING_SPRITE_Y, false);
            break;
        case TypeMoveAction::AIR_LEFT:
            setBuilder(builder,
                       (STARTING_SPRITE_X + SPRITE_SIZE * ((frameTicks / JUMPING_ANIMATION_SPEED) %
                                                           JUMPING_ANIMATION_FRAMES)),
                       JUMPING_SPRITE_Y, true);
            break;
        case TypeMoveAction::FLAP_NEUTRAL:
            setBuilder(builder, (STARTING_SPRITE_X + SPRITE_SIZE * FLAPPING_SPRITE_X_OFFSET),
                       FLAPPING_SPRITE_Y);
            break;
        case TypeMoveAction::FLAP_RIGHT:
            setBuilder(builder, (STARTING_SPRITE_X + SPRITE_SIZE * FLAPPING_SPRITE_X_OFFSET),
                       FLAPPING_SPRITE_Y, false);
            break;
        case TypeMoveAction::FLAP_LEFT:
            setBuilder(builder, (STARTING_SPRITE_X + SPRITE_SIZE * FLAPPING_SPRITE_X_OFFSET),
                       FLAPPING_SPRITE_Y, true);
            break;
        case TypeMoveAction::STAY_DOWN:
            setBuilder(builder, STARTING_SPRITE_X, LAY_DOWN_SPRITE_Y);
            break;
        case TypeMoveAction::NONE:
            setBuilder(builder, STARTING_SPRITE_X, STARTING_SPRITE_Y);
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

std::vector<ExplosionAnimation>& Animation::getExplosions(int playerId) {
    AnimationBuilder* builder = getAnimationBuilder(playerId);
    if (builder) {
        return builder->explosions;
    }

    static std::vector<ExplosionAnimation> noExplosions;
    return noExplosions;
}

std::vector<BombExplosion> Animation::getBombExplosions() { return explosions; }

float Animation::getIndicatorSprite(float width) {
    return width * ((frameTicks / INDICATOR_ANIMATION_SPEED) % INDICATOR_ANIMATION_FRAMES);
}

Animation::~Animation() = default;
