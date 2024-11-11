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
}

TextureType TextureContainer::indexToTextureType(int index) const {
    switch (index) {
        case 1:
            return TextureType::YELLOW_DUCK;
        case 2:
            return TextureType::GREY_DUCK;
        case 3:
            return TextureType::ORANGE_DUCK;
        case 4:
            return TextureType::WHITE_DUCK;
        case 5:
            return TextureType::BACKGROUND;
        case 6:
            return TextureType::TREE;
        case 7:
            return TextureType::BOX;
        case 8:
            return TextureType::COWBOY_GUN;
        case 9:
            return TextureType::CHEST_ARMOR;
        case 10:
            return TextureType::HELMET_ARMOR;
        default:
            throw std::out_of_range("Invalid texture index");
    }
}

SDL2pp::Texture& TextureContainer::getTexture(int index) {
    TextureType type = indexToTextureType(index);
    return textures.at(type);
}

SDL2pp::Texture& TextureContainer::getTexture(TextureType type) { return textures.at(type); }

TextureContainer::~TextureContainer() = default;
