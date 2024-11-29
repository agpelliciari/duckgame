#ifndef TEXTURE_CONTAINER_H
#define TEXTURE_CONTAINER_H

#include <filesystem>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

class TextureContainer {
private:
    SDL2pp::Texture noTexture;

    std::unordered_map<std::string, SDL2pp::Texture> textures;

    void loadTextures(SDL2pp::Renderer& renderer, const std::string& root);

    void recursiveLoadTextures(SDL2pp::Renderer& renderer, const std::string& root,
                               const std::string& path);

public:
    static constexpr const char* NO_TEXTURE = "/notexture.png";
    
    explicit TextureContainer(SDL2pp::Renderer& renderer);

    SDL2pp::Texture& getTexture(const std::string& source);

    ~TextureContainer();
};

#endif
