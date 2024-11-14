#include "texture_container.h"

TextureContainer::TextureContainer(SDL2pp::Renderer& renderer,
                                   const std::vector<std::string>& _textures_objs) {

    textures_blocks.reserve(_textures_objs.size());
    std::string data_path(&DATA_PATH[0]);
    data_path.append("/");
    for (const std::string& tex_path: _textures_objs) {
        // cppcheck-suppress useStlAlgorithm
        textures_blocks.emplace_back(renderer, data_path + tex_path);
    }

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
    textures.emplace(TextureType::SCOREBOARD,
                     SDL2pp::Texture(renderer, DATA_PATH "/leaderboard/scoreboard.png"));
    textures.emplace(TextureType::FONT, SDL2pp::Texture(renderer, DATA_PATH "/font/biosFont.png"));
}

SDL2pp::Texture& TextureContainer::getBlockTexture(int index) { return textures_blocks[index]; }

SDL2pp::Texture& TextureContainer::getTexture(TextureType type) { return textures.at(type); }

TextureContainer::~TextureContainer() = default;
