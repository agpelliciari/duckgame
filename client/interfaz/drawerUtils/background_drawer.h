#ifndef BACKGROUND_DRAWER_H
#define BACKGROUND_DRAWER_H

#include "object_drawer.h"
#include "../animation.h"

class BackgroundDrawer {
private:
    SDL2pp::Renderer& renderer;

    TextureContainer& textures;

    Camera& camera;

    const GameContext& context;

    Animation& animation;

    ObjectDrawer objectDrawer;
    
public:
    BackgroundDrawer(SDL2pp::Renderer& renderer, TextureContainer& textures, Camera& camera, const GameContext& context, Animation& animation);

    void draw(int screenWidth, int screenHeight);

    void drawObjects(const MatchDto& matchDto);

    void drawExplosions();

    ~BackgroundDrawer();
};

#endif
