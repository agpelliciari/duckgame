#ifndef TEXTURE_CONTAINER_H
#define TEXTURE_CONTAINER_H

#include <memory>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#define SIZE 2
#define YELLOW_DUCK_SPRITE 0
#define GREY_DUCK_SPRITE 1

class TextureContainer {
private:
    std::vector<std::unique_ptr<SDL2pp::Texture>> textures;  // cppcheck-suppress unusedStructMember

public:
    explicit TextureContainer(SDL2pp::Renderer& renderer);

    SDL2pp::Texture& getTexture(int index);

    ~TextureContainer();
};

#endif
