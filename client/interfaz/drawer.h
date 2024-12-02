#ifndef DRAWER_H
#define DRAWER_H

#include <algorithm>
#include <chrono>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "animation.h"
#include "camera.h"
#include "drawerUtils/player_drawer.h"
#include "texture_container.h"

#define INITIAL_SCREEN_WIDTH 640
#define INITIAL_SCREEN_HEIGHT 480

#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 16

#define IS_MAIN_PLAYER true
#define IS_SECONDARY_PLAYER false

class Drawer {
private:
    SDL2pp::SDLTTF ttf;

    SDL2pp::Font font;    

    SDL2pp::Window& window;

    SDL2pp::Renderer renderer;

    TextureContainer textures;

    Animation& animation;

    Camera& camera;

    const GameContext& context;

    PlayerDrawer playerDrawer;

    void drawBackground();

    void drawObjects(const MatchDto& matchDto);

    void drawMapObject(const MapObject& object);

    void drawDynamicObject(const DynamicObjDTO& object);

    void drawStatusBar(const MatchStatsInfo& stats);

    void drawLeaderboardBackground(double scaleX, double scaleY);

    void drawTrophy(double scaleX, double scaleY);

    void drawPlayerStats(const MatchStatsInfo& matchStats, double scaleX, double scaleY);

    void drawExplosions();

public:
    Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
           Camera& camera);

    // Once all the entities have been updated, we draw them to the screen.
    // This method will be responsible for drawing everything, including the games
    // UI.
    void draw(const MatchDto& matchDto, const MatchStatsInfo& stats);

    // Draw the leaderboard at the end of 5 rounds.
    void drawLeaderboard(const MatchStatsInfo& stats);

    // Draw the winner of the round.
    void drawWinner(const MatchStatsInfo& stats, const MatchDto& matchDto);

    void resetIndicatorFlag();

    ~Drawer();
};

#endif
