#include "drawer.h"

Drawer::Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
               Camera& camera):
        window(window),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer, gameContext.map.textures),
        animation(animation),
        camera(camera),
        context(gameContext),
        startTime(std::chrono::steady_clock::now()),
        showIndicators(true) {}

void Drawer::drawPlayer(const PlayerDTO& player) {
    static const std::unordered_map<int, TextureType> duckTextures = {{1, TextureType::YELLOW_DUCK},
                                                                      {2, TextureType::GREY_DUCK},
                                                                      {3, TextureType::ORANGE_DUCK},
                                                                      {4, TextureType::WHITE_DUCK}};

    auto mappedTexture = duckTextures.find(player.id);
    if (mappedTexture != duckTextures.end()) {
        const auto& playerTexture = mappedTexture->second;

        SDL_RendererFlip flip =
                animation.isFacingLeft(player.id) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        renderer.Copy(
                textures.getTexture(playerTexture),
                SDL2pp::Rect(animation.getSpriteX(player.id), animation.getSpriteY(player.id),
                             SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(camera.getScreenX(player.pos.x-BLOCK_WIDTH/2), camera.getScreenY(player.pos.y),
                             camera.getScaledSize(SPRITE_SIZE), camera.getScaledSize(SPRITE_SIZE)),
                0.0, SDL2pp::Point(0, 0), flip);

        if (player.weapon != TypeWeapon::NONE) {
            drawWeapon(player, flip);
        }

        drawArmor(player, flip);
    }
}

void Drawer::drawIndicator(const PlayerDTO& player, bool isMainPlayer) {
    SDL2pp::Rect indicatorType;

    float spriteX = animation.getIndicatorSprite(INDICATOR_WIDTH);

    if (isMainPlayer) {
        indicatorType = SDL2pp::Rect(spriteX, 0, INDICATOR_WIDTH, INDICATOR_HEIGHT);
    } else {
        indicatorType = SDL2pp::Rect(spriteX, INDICATOR_HEIGHT, INDICATOR_WIDTH, INDICATOR_HEIGHT);
    }

    renderer.Copy(
            textures.getTexture(TextureType::PLAYER_INDICATOR), indicatorType,
            SDL2pp::Rect(camera.getScreenX(player.pos.x + 8), camera.getScreenY(player.pos.y - 25),
                         camera.getScaledSize(INDICATOR_WIDTH_RESIZED),
                         camera.getScaledSize(INDICATOR_HEIGHT_RESIZED)));
}

void Drawer::drawArmor(const PlayerDTO& player, SDL_RendererFlip flip) {

    if (player.helmet) {
        renderer.Copy(
                textures.getTexture(TextureType::HELMET_ARMOR),
                SDL2pp::Rect(0, 0, SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(
                        camera.getScreenX(player.pos.x + getTextureFlipValue(flip, HELMET_FLIP_X,
                                                                             HELMET_UNFLIP_X)),
                        camera.getScreenY(player.pos.y - 10), camera.getScaledSize(SPRITE_SIZE),
                        camera.getScaledSize(SPRITE_SIZE)),
                0.0, SDL2pp::Point(0, 0), flip);
    }


    if (player.chest_armor) {
        renderer.Copy(
                textures.getTexture(TextureType::CHEST_ARMOR),
                SDL2pp::Rect(0, 0, SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(camera.getScreenX(player.pos.x), camera.getScreenY(player.pos.y + 3),
                             camera.getScaledSize(SPRITE_SIZE), camera.getScaledSize(SPRITE_SIZE)),
                0.0, SDL2pp::Point(0, 0), flip);
    }
}

void Drawer::drawWeapon(const PlayerDTO& player, SDL_RendererFlip flip) {
    static const std::unordered_map<TypeWeapon, std::tuple<TextureType, int, int>> weaponTextures =
            {
                    // almaceno enum de textura del container y dimensiones
                    {TypeWeapon::PISTOLA_COWBOY,
                     {TextureType::COWBOY_GUN, COWBOY_GUN_WIDTH, COWBOY_GUN_HEIGHT}}
                    // demas armas
            };

    auto weaponTexture = weaponTextures.find(player.weapon);
    if (weaponTexture != weaponTextures.end()) {
        const auto& [textureType, width, height] = weaponTexture->second;

        renderer.Copy(
                textures.getTexture(textureType), SDL2pp::Rect(0, 0, width, height),
                SDL2pp::Rect(camera.getScreenX(player.pos.x +
                                               getTextureFlipValue(flip, GUN_FLIP_X, GUN_UNFLIP_X)),
                             camera.getScreenY(player.pos.y + (SPRITE_SIZE / 2)),
                             camera.getScaledSize(width - 6), camera.getScaledSize(height - 6)),
                0.0, SDL2pp::Point(0, 0), flip);
    }
}

int Drawer::getTextureFlipValue(SDL_RendererFlip flip, int flipValue, int unflipValue) {
    return flip == SDL_FLIP_HORIZONTAL ? flipValue : unflipValue;
}

void Drawer::drawBackground() {
    int scaledWidth = camera.backgroundScaledSize(window.GetWidth());
    int scaledHeight = camera.backgroundScaledSize(window.GetHeight());

    renderer.Copy(textures.getTexture(TextureType::BACKGROUND),
                  SDL2pp::Rect((window.GetWidth() - scaledWidth) / 2, (window.GetHeight() - scaledHeight) / 2,
                               scaledWidth, scaledHeight),
                  SDL2pp::Rect(0, 0, window.GetWidth(), window.GetHeight()));
}

void Drawer::drawObjects(const MatchDto& matchDto) {
    // inicialmente se dibuja como si todos fueran objects.    
    for (const MapObject& object: context.map.objects) {
        renderer.Copy(
                textures.getBlockTexture(object.ind_texture), SDL2pp::Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT),
                SDL2pp::Rect(camera.getScreenX(object.column), 
                             camera.getScreenY(object.row + BLOCK_HEIGHT), camera.getScaledSize(BLOCK_WIDTH),
                             camera.getScaledSize(BLOCK_HEIGHT)));
    }

    for (const auto& object: matchDto.objects) {

        if (object.type == TypeDynamicObject::BOX) {
            renderer.Copy(
                    textures.getTexture(TextureType::BOX), SDL2pp::Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y+BLOCK_HEIGHT*2),
                                 camera.getScaledSize(BLOCK_WIDTH), camera.getScaledSize(BLOCK_HEIGHT)));

        } else if (object.type == TypeDynamicObject::PISTOLA_COWBOY) {
            renderer.Copy(
                    textures.getTexture(TextureType::COWBOY_GUN), SDL2pp::Rect(0, 0, 22, 11),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                 camera.getScaledSize(22 - 6), camera.getScaledSize(11 - 6)));
        }
    }
}

void Drawer::updateIndicatorFlag() {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime =
            std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    showIndicators = elapsedTime < INDICATOR_MAX_TIME;
}

void Drawer::draw(const MatchDto& matchDto) {
    renderer.Clear();

    drawBackground();

    drawObjects(matchDto);

    updateIndicatorFlag();

    for (const PlayerDTO& player: matchDto.players) {

        if (showIndicators) {
            if (player.id == context.first_player) {
                drawIndicator(player, IS_MAIN_PLAYER);
            } else if ((context.dualplay) && (player.id == context.second_player)) {
                drawIndicator(player, IS_SECONDARY_PLAYER);
            }
        }

        drawPlayer(player);
    }

    // Show rendered frame
    renderer.Present();
}

Drawer::~Drawer() = default;
