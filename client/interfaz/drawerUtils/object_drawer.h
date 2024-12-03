#ifndef OBJECT_DRAWER_H
#define OBJECT_DRAWER_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../texture_container.h"
#include "../camera.h"
#include "client/gamecontext.h"
#include "common/clientprotocol.h"
#include "weapon_builder.h"

#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 16

class ObjectDrawer {
private:
    SDL2pp::Renderer& renderer;

    TextureContainer& textures;

    Camera& camera;

    const GameContext& context;
public:
    ObjectDrawer(SDL2pp::Renderer& renderer, TextureContainer& textures, Camera& camera, const GameContext& context);

    void draw(const MapObject& object);

    void draw(const DynamicObjDTO& object);

    ~ObjectDrawer();
};

#endif
