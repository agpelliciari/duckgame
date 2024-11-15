#ifndef TEXTURE_CONTAINER_H
#define TEXTURE_CONTAINER_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include <unordered_map>
#include <filesystem>
#include <string>

class TextureContainer {
public:
    /* DUCKS */
    static constexpr const char* YELLOW_DUCK = "duck_sprites/yellow_duck.png";
    static constexpr const char* GREY_DUCK = "duck_sprites/grey_duck.png";
    static constexpr const char* ORANGE_DUCK = "duck_sprites/orange_duck.png";
    static constexpr const char* WHITE_DUCK = "duck_sprites/white_duck.png";

    /* MAP */
    static constexpr const char* BOX = "boxes/itemBox1.png";

    /* WEAPONS */
    static constexpr const char* COWBOY_GUN = "weapons/cowboyPistol.png";

    /* ARMORS */
    static constexpr const char* CHEST_ARMOR = "armors/chestPlateAnim.png";
    static constexpr const char* HELMET_ARMOR = "armors/helmet.png";

    /* UI */
    static constexpr const char* PLAYER_INDICATOR = "duck_sprites/playerIndicator.png";
    static constexpr const char* SCOREBOARD = "leaderboard/scoreboard.png";
    static constexpr const char* FONT = "font/biosFont.png";

private:
    SDL2pp::Texture noTexture;
    std::unordered_map<std::string, SDL2pp::Texture> textures;

public:
    explicit TextureContainer(SDL2pp::Renderer& renderer);

    SDL2pp::Texture& getTexture(const std::string& source);

    ~TextureContainer();

private:
    void loadTextures(SDL2pp::Renderer& renderer, const std::string& root);

    void recursiveLoadTextures(SDL2pp::Renderer& renderer, const std::string& root, const std::string& path);
};

#endif
