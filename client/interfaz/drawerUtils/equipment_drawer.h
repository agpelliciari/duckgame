#ifndef EQUIPMENT_DRAWER_H
#define EQUIPMENT_DRAWER_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../texture_container.h"
#include "../camera.h"
#include "common/dtosplayer.h"

class EquipmentDrawer {
protected:
    SDL2pp::Renderer& renderer;

    TextureContainer& textures;

    Camera& camera;

    int getTextureFlipValue(SDL_RendererFlip flip, int flipValue, int unflipValue) {
        return flip == SDL_FLIP_HORIZONTAL ? flipValue : unflipValue;
    }

public:
    EquipmentDrawer(SDL2pp::Renderer& renderer, TextureContainer& textures, Camera& camera)
        : renderer(renderer), textures(textures), camera(camera) {}

    virtual void draw(const PlayerDTO& player, SDL_RendererFlip flip) = 0;

    virtual void drawInfo(const PlayerDTO& player) = 0;

    virtual ~EquipmentDrawer() {}
};

#endif
