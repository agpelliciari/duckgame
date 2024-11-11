#ifndef TEXTURE_CONTAINER_H
#define TEXTURE_CONTAINER_H

#include <memory>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

enum class TextureType {
    YELLOW_DUCK = 1,
    GREY_DUCK,
    ORANGE_DUCK,
    WHITE_DUCK,

    BACKGROUND,
    TREE,
    BOX,
    COWBOY_GUN,
    CHEST_ARMOR,
    HELMET_ARMOR
};

class TextureContainer {
private:
    std::unordered_map<TextureType, SDL2pp::Texture>
            textures;  // cppcheck-suppress unusedStructMember

public:
    explicit TextureContainer(SDL2pp::Renderer& renderer);

    SDL2pp::Texture& getTexture(TextureType type);

    ~TextureContainer();
};

#endif
