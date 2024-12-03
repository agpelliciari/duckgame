#include "explosion_animation.h"

ExplosionAnimation::ExplosionAnimation(std::string texture, int size, float duration, int frames)
    : texture(texture), spriteSize(size), duration(duration),
      animationTime(0), totalFrames(frames), currentFrame(0) {}

void ExplosionAnimation::update(float deltaTime) {
    animationTime += deltaTime;
    if (animationTime >= duration) {
        return;
    }
    currentFrame = static_cast<int>((animationTime / duration) * totalFrames);
}

bool ExplosionAnimation::isFinished() const {
    return animationTime >= duration;
}

std::string ExplosionAnimation::getTexture() const {
    return texture;
}

int ExplosionAnimation::getSpriteSize() const {
    return spriteSize;
}

int ExplosionAnimation::getCurrentFrame() const {
    return currentFrame;
}

ExplosionAnimation::~ExplosionAnimation() = default;
