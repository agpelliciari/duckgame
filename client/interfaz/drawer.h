#ifndef DRAWER_H
#define DRAWER_H

#include <chrono>
#include <tuple>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "animation.h"
#include "camera.h"
#include "texture_container.h"

#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 16

#define COWBOY_GUN_WIDTH 22
#define COWBOY_GUN_HEIGHT 11

#define INDICATOR_WIDTH 18.2f
#define INDICATOR_WIDTH_RESIZED 14
#define INDICATOR_HEIGHT_RESIZED 30
#define INDICATOR_HEIGHT 33.5f
#define INDICATOR_MAX_TIME 5

#define GUN_FLIP_X -1
#define GUN_UNFLIP_X 16
#define HELMET_FLIP_X 3
#define HELMET_UNFLIP_X -3

#define IS_MAIN_PLAYER true
#define IS_SECONDARY_PLAYER false

class Drawer {
private:
    SDL2pp::Window& window;

    SDL2pp::Renderer renderer;

    TextureContainer textures;

    Animation& animation;

    Camera& camera;

    const GameContext& context;

    std::chrono::time_point<std::chrono::steady_clock> startTime;

    bool showIndicators;  // cppcheck-suppress unusedStructMember

    void updateIndicatorFlag();

    void drawPlayer(const PlayerDTO& player);

    void drawIndicator(const PlayerDTO& player, bool isMainPlayer);

    void drawWeapon(const PlayerDTO& player, SDL_RendererFlip flip);

    int getTextureFlipValue(SDL_RendererFlip flip, int flipValue, int unflipValue);

    void drawArmor(const PlayerDTO& player, SDL_RendererFlip flip);

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
