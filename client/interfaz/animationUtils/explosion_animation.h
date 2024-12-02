#ifndef EXPLOSION_ANIMATION_H
#define EXPLOSION_ANIMATION_H

#include <string>

#include "common/dtosobject.h"

class ExplosionAnimation {
private:
    std::string texture;

    int spriteSize;

    float duration;

    float animationTime;

    int totalFrames;
    
    int currentFrame;

public:
    ExplosionAnimation(std::string texture, int size, float duration, int frames);

    void update(float deltaTime);

    bool isFinished() const;

    std::string getTexture() const;

    int getSpriteSize() const;

    int getCurrentFrame() const;

    virtual ~ExplosionAnimation();
};

class BombExplosion : public ExplosionAnimation {
private:
    MapPoint position;

public:
    BombExplosion(MapPoint pos, std::string texture, int size, float duration, int frames)
        : ExplosionAnimation(texture, size, duration, frames), position(pos) {}

    const MapPoint& getPosition() const { return position; }
};

#endif
