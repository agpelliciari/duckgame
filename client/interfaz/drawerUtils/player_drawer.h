#ifndef PLAYER_DRAWER_H
#define PLAYER_DRAWER_H

#include <algorithm>
#include <chrono>

#include "weapon_drawer.h"
#include "armor_drawer.h"

#define X_PHYSICAL_OFFSET_PLAYER 8
#define Y_PHYSICAL_OFFSET_PLAYER 1

#define INDICATOR_WIDTH 18.2f
#define INDICATOR_WIDTH_RESIZED 14
#define INDICATOR_HEIGHT_RESIZED 30
#define INDICATOR_HEIGHT 33.5f
#define INDICATOR_MAX_TIME 5

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

    std::chrono::time_point<std::chrono::steady_clock> startTime;

    bool showIndicators;  // cppcheck-suppress unusedStructMember

public:
    PlayerDrawer(SDL2pp::Font& font, SDL2pp::Renderer& renderer, TextureContainer& textures, Animation& animation, Camera& camera);

    void draw(const PlayerDTO& player);

    void drawInfo(const PlayerDTO& player, const std::string color);

    void drawStats(const PlayerStatDto& playerStat, double scaleX, double scaleY, int& y, int rowSpacing);

    void drawIndicator(const PlayerDTO& player, bool isMainPlayer);

    void updateIndicatorFlag();

    void resetIndicatorFlag();

    bool getIndicatorFlag();

    ~PlayerDrawer();
};


#endif
