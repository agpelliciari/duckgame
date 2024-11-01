#ifndef DRAWER_H
#define DRAWER_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "animation.h"
#include "texture_container.h"

#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32

class Drawer {
private:
    SDL2pp::Renderer renderer;

    TextureContainer textures;

    Animation& animation;

    uint8_t playerId;  // cppcheck-suppress unusedStructMember

    void drawPlayer(const PlayerDTO& player);

public:
    Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext);

    // Once all the entities have been updated, we draw them to the screen.
    // This method will be responsible for drawing everything, including the games
    // UI.
    void draw(const MatchDto& matchDto);

    ~Drawer();
};

#endif
