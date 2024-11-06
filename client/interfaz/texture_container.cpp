#include "texture_container.h"

TextureContainer::TextureContainer(SDL2pp::Renderer& renderer) {
    textures.emplace(TextureType::YELLOW_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/yellow_duck.png"));
    textures.emplace(TextureType::GREY_DUCK, SDL2pp::Texture(renderer, DATA_PATH "/grey_duck.png"));
    textures.emplace(TextureType::ORANGE_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/orange_duck.png"));
    textures.emplace(TextureType::WHITE_DUCK,
                     SDL2pp::Texture(renderer, DATA_PATH "/white_duck.png"));
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
            return TextureType::PLATFORM;
        default:
            throw std::out_of_range("Invalid texture index");
    }
}

SDL2pp::Texture& TextureContainer::getTexture(int index) {
    TextureType type = indexToTextureType(index);
    return textures.at(type);
}

TextureContainer::~TextureContainer() = default;
