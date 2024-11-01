#include "drawer.h"

Drawer::Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext):
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer),
        animation(animation),
        playerId(gameContext.first_player) {}

void Drawer::drawPlayer(const PlayerDTO& player) {
    // Determine the flip mode based on the last direction
    SDL_RendererFlip flip = animation.isFacingLeft(player.id) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    // Draw player sprite
    renderer.Copy(textures.getTexture(player.id),
                  SDL2pp::Rect(animation.getSpriteX(player.id), animation.getSpriteY(player.id),
                               SPRITE_WIDTH, SPRITE_HEIGHT),
                  SDL2pp::Rect(player.coord_x, player.coord_y, 50, 50), 0.0, SDL2pp::Point(0, 0),
                  flip);
}

void Drawer::draw(const MatchDto& matchDto) {
    // Clear screen
    renderer.SetDrawColor(255, 255, 255, 255);  // White background
    renderer.Clear();

    const PlayerDTO* mainPlayer = nullptr;

    for (const PlayerDTO& player: matchDto.players) {
        if (player.id == playerId) {
            mainPlayer = &player;
            continue;
        }
        drawPlayer(player);
    }

    if (mainPlayer) {
        drawPlayer(*mainPlayer);
    }

    // Show rendered frame
    renderer.Present();
}

Drawer::~Drawer() = default;
