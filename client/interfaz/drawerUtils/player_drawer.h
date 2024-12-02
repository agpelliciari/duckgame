#ifndef PLAYER_DRAWER_H
#define PLAYER_DRAWER_H

#include "weapon_drawer.h"
#include "armor_drawer.h"

#define X_PHYSICAL_OFFSET_PLAYER 8
#define Y_PHYSICAL_OFFSET_PLAYER 1

class PlayerDrawer {
private:
    SDL2pp::Font& font;

    SDL2pp::Renderer& renderer;

    TextureContainer& textures;

    Animation& animation;

    Camera& camera;

    std::unordered_map<int, std::string> duckTextures;

    WeaponDrawer weaponDrawer;

    ArmorDrawer armorDrawer;
public:
    PlayerDrawer(SDL2pp::Font& font, SDL2pp::Renderer& renderer, TextureContainer& textures, Animation& animation, Camera& camera);

    void draw(const PlayerDTO& player);

    void drawInfo(const PlayerDTO& player, const std::string color);

    void drawStats(const PlayerStatDto& playerStat, double scaleX, double scaleY, int& y, int rowSpacing);

    ~PlayerDrawer();
};


#endif
