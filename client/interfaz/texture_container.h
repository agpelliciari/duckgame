#ifndef TEXTURE_CONTAINER_H
#define TEXTURE_CONTAINER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

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
    HELMET_ARMOR,
    PLAYER_INDICATOR,
    SCOREBOARD,
    FONT, 
    SIMPLE_BULLET
};

class TextureContainer {
private:
    std::unordered_map<TextureType, SDL2pp::Texture>
            textures;                              // cppcheck-suppress unusedStructMember
    std::vector<SDL2pp::Texture> textures_blocks;  // cppcheck-suppress unusedStructMember

public:
    explicit TextureContainer(SDL2pp::Renderer& renderer,
                              const std::vector<std::string>& _textures, const std::string& background);

    SDL2pp::Texture& getTexture(TextureType type);

    SDL2pp::Texture& getBlockTexture(int index);

    ~TextureContainer();
};

#endif
