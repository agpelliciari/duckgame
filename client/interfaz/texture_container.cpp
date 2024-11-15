#include "texture_container.h"

TextureContainer::TextureContainer(SDL2pp::Renderer& renderer): noTexture(SDL2pp::Texture(renderer, std::string(DATA_PATH) + "/notexture.png")) {
    loadTextures(renderer, DATA_PATH);
}

SDL2pp::Texture& TextureContainer::getTexture(const std::string& source) {
    try {
        return textures.at(source);
    } catch (const std::out_of_range& e) {
        std::cout << "Texture not found: " << source << std::endl;
        return noTexture;
    }
}

TextureContainer::~TextureContainer() = default;

void TextureContainer::loadTextures(SDL2pp::Renderer& renderer, const std::string& root) {
    for (const auto& entry : std::filesystem::directory_iterator(root)) {
        if (entry.is_directory())
            recursiveLoadTextures(renderer, root, entry.path().string());
    }
}

void TextureContainer::recursiveLoadTextures(SDL2pp::Renderer& renderer, const std::string& root, const std::string& path) {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            recursiveLoadTextures(renderer, root, entry.path().string());
        } else if (entry.is_regular_file() && entry.path().extension() == ".png") {
            std::string relative_path = entry.path().string().substr(root.size());
            textures.emplace(relative_path, SDL2pp::Texture(renderer, entry.path().string()));
        }
    }
}
