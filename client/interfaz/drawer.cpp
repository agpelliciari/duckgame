#include "drawer.h"

Drawer::Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
               Camera& camera):
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer),
        animation(animation),
        camera(camera),
        context(gameContext) {}

void Drawer::drawPlayer(const PlayerDTO& player) {
    SDL_RendererFlip flip = animation.isFacingLeft(player.id) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    renderer.Copy(
            textures.getTexture(player.id),
            SDL2pp::Rect(animation.getSpriteX(player.id), animation.getSpriteY(player.id),
                         SPRITE_WIDTH, SPRITE_HEIGHT),
            SDL2pp::Rect(camera.getScreenX(player.pos.x), camera.getScreenY(player.pos.y),
                         camera.getScaledSize(SPRITE_WIDTH), camera.getScaledSize(SPRITE_HEIGHT)),
            0.0, SDL2pp::Point(0, 0), flip);

    if (player.weapon != TypeWeapon::NONE) {
        drawWeapon(player, flip);
    }

    drawArmor(player, flip);
}

void Drawer::drawArmor(const PlayerDTO& player, SDL_RendererFlip flip) {

    if (player.helmet) {
        renderer.Copy(
                textures.getTexture(TextureType::HELMET_ARMOR),
                SDL2pp::Rect(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT),
                SDL2pp::Rect(
                        camera.getScreenX(player.pos.x + getTextureFlipValue(flip, HELMET_FLIP_X,
                                                                             HELMET_UNFLIP_X)),
                        camera.getScreenY(player.pos.y - 10), camera.getScaledSize(SPRITE_WIDTH),
                        camera.getScaledSize(SPRITE_HEIGHT)),
                0.0, SDL2pp::Point(0, 0), flip);
    }


    if (player.chest_armor) {
        renderer.Copy(
                textures.getTexture(TextureType::CHEST_ARMOR),
                SDL2pp::Rect(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT),
                SDL2pp::Rect(camera.getScreenX(player.pos.x), camera.getScreenY(player.pos.y + 3),
                             camera.getScaledSize(SPRITE_WIDTH),
                             camera.getScaledSize(SPRITE_HEIGHT)),
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
                             camera.getScreenY(player.pos.y + (SPRITE_HEIGHT / 2)),
                             camera.getScaledSize(width - 6), camera.getScaledSize(height - 6)),
                0.0, SDL2pp::Point(0, 0), flip);
    }
}

int Drawer::getTextureFlipValue(SDL_RendererFlip flip, int flipValue, int unflipValue) {
    return flip == SDL_FLIP_HORIZONTAL ? flipValue : unflipValue;
}

void Drawer::drawBackground() {
    int scaledWidth = camera.backgroundScaledSize(SCREEN_WIDTH);
    int scaledHeight = camera.backgroundScaledSize(SCREEN_HEIGHT);

    renderer.Copy(textures.getTexture(TextureType::BACKGROUND),
                  SDL2pp::Rect((SCREEN_WIDTH - scaledWidth) / 2, (SCREEN_HEIGHT - scaledHeight) / 2,
                               scaledWidth, scaledHeight),
                  SDL2pp::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void Drawer::drawObjects(const MatchDto& matchDto) {
    // inicialmente dibujo solo los primeros 4 elementos del .yaml
    /*for (int i = 0; i < 4; i++) {

        renderer.Copy(textures.getTexture((int)context.blocks[i].texture),
                      SDL2pp::Rect(0, 0, 73, 93),
                      SDL2pp::Rect(camera.getScreenX(context.blocks[i].pos.x),
                                   camera.getScreenY(context.blocks[i].pos.y),
                                   camera.getScaledSize(73), camera.getScaledSize(93)));
    }*/

    // dibujo los objetos de la partida -> luego agregar en una funcion
    for (const auto& object: matchDto.objects) {

        if (object.type == TypeDynamicObject::BOX) {
            renderer.Copy(
                    textures.getTexture(TextureType::BOX), SDL2pp::Rect(0, 16, 16, 16),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                 camera.getScaledSize(16), camera.getScaledSize(16)));

        } else if (object.type == TypeDynamicObject::PISTOLA_COWBOY) {
            renderer.Copy(
                    textures.getTexture(TextureType::COWBOY_GUN), SDL2pp::Rect(0, 0, 22, 11),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                 camera.getScaledSize(22 - 6), camera.getScaledSize(11 - 6)));
        }
    }
}

void Drawer::draw(const MatchDto& matchDto) {
    // Clear screen
    renderer.SetDrawColor(255, 255, 255, 255);  // White background
    renderer.Clear();

    drawBackground();

    drawObjects(matchDto);

    const PlayerDTO* mainPlayer = nullptr;

    for (const PlayerDTO& player: matchDto.players) {
        if (player.id == context.first_player) {
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
