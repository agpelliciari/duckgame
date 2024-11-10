#ifndef DRAWER_H
#define DRAWER_H

#include <tuple>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "animation.h"
#include "camera.h"
#include "texture_container.h"

#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32

#define COWBOY_GUN_WIDTH 22
#define COWBOY_GUN_HEIGHT 11

#define FLIP -1
#define UNFLIP 16

class Drawer {
private:
    SDL2pp::Renderer renderer;

    TextureContainer textures;

    Animation& animation;

    Camera& camera;

    const GameContext& context;

    void drawPlayer(const PlayerDTO& player);

    void drawWeapon(const PlayerDTO& player, SDL_RendererFlip flip);

    int getWeaponFlip(SDL_RendererFlip flip);

    void drawBackground();

    void drawObjects(const MatchDto& matchDto);

public:
    Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
           Camera& camera);

    // Once all the entities have been updated, we draw them to the screen.
    // This method will be responsible for drawing everything, including the games
    // UI.
    void draw(const MatchDto& matchDto);

    ~Drawer();
};

#endif
