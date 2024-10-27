#include "texture_container.h"

TextureContainer::TextureContainer(SDL2pp::Renderer& renderer): textures(SIZE) {
    textures.emplace_back(
            std::make_unique<SDL2pp::Texture>(renderer, DATA_PATH "/yellow_duck.png"));
    textures.emplace_back(std::make_unique<SDL2pp::Texture>(renderer, DATA_PATH "/grey_duck.png"));
}

SDL2pp::Texture& TextureContainer::getTexture(int index) { return *textures.at(index); }

TextureContainer::~TextureContainer() = default;
