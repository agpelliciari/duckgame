#include "texture_container.h"

TextureContainer::TextureContainer(SDL2pp::Renderer& renderer) {
    textures.emplace(TextureType::YELLOW_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/duck_sprites/yellow_duck.png"));
    textures.emplace(TextureType::GREY_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/duck_sprites/grey_duck.png"));
    textures.emplace(TextureType::ORANGE_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/duck_sprites/orange_duck.png"));
    textures.emplace(TextureType::WHITE_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/duck_sprites/white_duck.png"));
    textures.emplace(TextureType::BACKGROUND,
                     SDL2pp::Texture(renderer, DATA_PATH "/backgrounds/virtual.png"));
    textures.emplace(TextureType::TREE, SDL2pp::Texture(renderer, DATA_PATH "/notexture.png"));
    textures.emplace(TextureType::BOX, SDL2pp::Texture(renderer, DATA_PATH "/boxes/itemBox1.png"));
    textures.emplace(TextureType::COWBOY_GUN,
                     SDL2pp::Texture(renderer, DATA_PATH "/weapons/cowboyPistol.png"));
    textures.emplace(TextureType::CHEST_ARMOR,
                     SDL2pp::Texture(renderer, DATA_PATH "/armors/chestPlateAnim.png"));
    textures.emplace(TextureType::HELMET_ARMOR,
                     SDL2pp::Texture(renderer, DATA_PATH "/armors/helmet.png"));
    textures.emplace(TextureType::PLAYER_INDICATOR,
                     SDL2pp::Texture(renderer, DATA_PATH "/duck_sprites/playerIndicator.png"));
}

SDL2pp::Texture& TextureContainer::getTexture(TextureType type) { return textures.at(type); }

TextureContainer::~TextureContainer() = default;
