#include "background_drawer.h"

BackgroundDrawer::BackgroundDrawer(SDL2pp::Renderer& renderer, TextureContainer& textures, Camera& camera, const GameContext& context, Animation& animation) :
        renderer(renderer), textures(textures), camera(camera), context(context), animation(animation), objectDrawer(renderer, textures, camera, context) {}

void BackgroundDrawer::draw(int screenWidth, int screenHeight) {
    const float PARALLAX_OFFSET_FACTOR = 0.5f;

    SDL_Rect visibleSection =
            camera.backgroundVisibleSection(screenWidth, screenHeight, PARALLAX_OFFSET_FACTOR);

    renderer.Copy(
            textures.getTexture(context.map.background),
            SDL2pp::Rect(visibleSection.x, visibleSection.y, visibleSection.w, visibleSection.h),
            SDL2pp::Rect(0, 0, screenWidth, screenHeight));
}

void BackgroundDrawer::drawObjects(const MatchDto& matchDto) {
    for (const MapObject& object: context.map.objects) {
        objectDrawer.draw(object);
    }

    for (const DynamicObjDTO& object: matchDto.objects) {
        objectDrawer.draw(object);
    }
}

void BackgroundDrawer::drawExplosions() {
    for (const BombExplosion& explosion: animation.getBombExplosions()) {
        int size = explosion.getSpriteSize();
        MapPoint pos = explosion.getPosition();
        renderer.Copy(
                textures.getTexture(explosion.getTexture()),
                SDL2pp::Rect(explosion.getCurrentFrame() * size, 0, size, size),
                SDL2pp::Rect(camera.getScreenX(pos.x) - 50 , camera.getScreenY(-pos.y) - 50,
                             camera.getScaledSize(size),
                             camera.getScaledSize(size)));
    }
}

BackgroundDrawer::~BackgroundDrawer() = default;
