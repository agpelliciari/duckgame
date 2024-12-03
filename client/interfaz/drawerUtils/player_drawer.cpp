#include "player_drawer.h"

PlayerDrawer::PlayerDrawer(SDL2pp::Font& font, SDL2pp::Renderer& renderer, TextureContainer& textures, Animation& animation, Camera& camera):
        font(font),
        renderer(renderer),
        textures(textures),
        animation(animation),
        camera(camera),
        weaponDrawer(font, renderer, textures, animation, camera),
        armorDrawer(renderer, textures, camera),
        startTime(std::chrono::steady_clock::now()),
        showIndicators(true) {
            duckTextures = {{1, "/duck_sprites/duck_white.png"},
                            {2, "/duck_sprites/duck_yellow.png"},
                            {3, "/duck_sprites/duck_grey.png"},
                            {4, "/duck_sprites/duck_orange.png"}};
}

void PlayerDrawer::draw(const PlayerDTO& player) {
    const std::string playerTexture;
    auto mappedTexture = duckTextures.find(player.id);
    if (mappedTexture != duckTextures.end()) {
        const auto& playerTexture = mappedTexture->second;

        SDL_RendererFlip flip =
                animation.isFacingLeft(player.id) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        renderer.Copy(
                textures.getTexture(playerTexture),
                SDL2pp::Rect(animation.getSpriteX(player.id), animation.getSpriteY(player.id),
                             SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(camera.getScreenX(player.pos.x - X_PHYSICAL_OFFSET_PLAYER),
                             camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER - 16),
                             camera.getScaledSize(SPRITE_SIZE), camera.getScaledSize(SPRITE_SIZE)),
                0.0, SDL2pp::Point(0, 0), flip);

        armorDrawer.draw(player, flip);

        if (player.weapon != TypeWeapon::NONE) {
            weaponDrawer.draw(player, flip);
        }

        if (player.is_alive) {
            drawInfo(player, playerTexture);
        }
    }
}

void PlayerDrawer::drawInfo(const PlayerDTO& player, const std::string color) {
    renderer.Copy(textures.getTexture(color), SDL2pp::Rect(1, 10, 32, 10),
                  SDL2pp::Rect(12 + 115 * (player.id - 1), 8, 32, 14));
    
    int health;
    if (player.hp > 3) {
        health = 16;
    } else {
        health = (5 * player.hp) + 1;
    }
    
    renderer.Copy(textures.getTexture("/ui/hp.png"), SDL2pp::Rect(0, 0, health, 16),
                        SDL2pp::Rect(35 + 115 * (player.id - 1), 5, health, 20));

    if (player.weapon != TypeWeapon::NONE) {
        weaponDrawer.drawInfo(player);
    }

    armorDrawer.drawInfo(player);
}

void PlayerDrawer::drawStats(const PlayerStatDto& playerStat, double scaleX, double scaleY, int& y, int rowSpacing) {
    auto mappedTexture = duckTextures.find(static_cast<int>(playerStat.id));
    if (mappedTexture != duckTextures.end()) {
        const auto& playerTexture = mappedTexture->second;

        int playerSpriteX = static_cast<int>(165 * scaleX);
        int playerSpriteSizeWidth = static_cast<int>(64 * scaleX);
        int playerSpriteSizeHeight = static_cast<int>(64 * scaleY);

        renderer.Copy(
            textures.getTexture(playerTexture),
            SDL2pp::Rect(1, 10, SPRITE_SIZE, SPRITE_SIZE),
            SDL2pp::Rect(playerSpriteX, y, playerSpriteSizeWidth, playerSpriteSizeHeight)
        );

        int winsX = static_cast<int>(250 * scaleX);
        int winsSizeWidth = static_cast<int>(20 * scaleX);
        int winsSizeHeight = static_cast<int>(20 * scaleY);

        std::string text = std::to_string(static_cast<int>(playerStat.wins));

        SDL2pp::Texture text_sprite(renderer, font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));

        renderer.Copy(text_sprite, SDL2pp::NullOpt, SDL2pp::Rect(winsX, y + 15, winsSizeWidth, winsSizeHeight));
    }

    y += rowSpacing;
}

void PlayerDrawer::drawIndicator(const PlayerDTO& player, bool isMainPlayer) {
    SDL2pp::Rect indicatorType;

    float spriteX = animation.getIndicatorSprite(INDICATOR_WIDTH);

    if (isMainPlayer) {
        indicatorType = SDL2pp::Rect(spriteX, 0, INDICATOR_WIDTH, INDICATOR_HEIGHT);
    } else {
        indicatorType = SDL2pp::Rect(spriteX, INDICATOR_HEIGHT, INDICATOR_WIDTH, INDICATOR_HEIGHT);
    }

    renderer.Copy(textures.getTexture("/duck_sprites/playerIndicator.png"), indicatorType,
                  SDL2pp::Rect(camera.getScreenX(player.pos.x - X_PHYSICAL_OFFSET_PLAYER + 9),
                               camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER - 40),
                               camera.getScaledSize(INDICATOR_WIDTH_RESIZED),
                               camera.getScaledSize(INDICATOR_HEIGHT_RESIZED)));
}

void PlayerDrawer::updateIndicatorFlag() {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime =
            std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    showIndicators = elapsedTime < INDICATOR_MAX_TIME;
}

void PlayerDrawer::resetIndicatorFlag() {
    startTime = std::chrono::steady_clock::now();
    showIndicators = true;
}

bool PlayerDrawer::getIndicatorFlag() {
    return showIndicators;
}

PlayerDrawer::~PlayerDrawer() = default;
