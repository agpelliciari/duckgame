#include "drawer.h"

Drawer::Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
               Camera& camera):
        font(DATA_PATH "/font/pixelFont.ttf", 20),
        window(window),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer),
        camera(camera),
        context(gameContext),
        playerDrawer(font, renderer, textures, animation, camera),
        backgroundDrawer(renderer, textures, camera, context, animation) {}

void Drawer::resetIndicatorFlag() {
    playerDrawer.resetIndicatorFlag();
}

void Drawer::drawStatusBar(const MatchStatsInfo& stats) {
    int screenWidth = window.GetWidth();
    renderer.Copy(textures.getTexture("/ui/statusBar.png"), SDL2pp::Rect(0, 0, 260, 13),
                  SDL2pp::Rect(0, 0, screenWidth, 30));

    std::string text;
    SDL2pp::Rect destRect;

    if (stats.state == INICIADA) {
        text += "ROUND " + std::to_string(stats.numronda);
        destRect = SDL2pp::Rect(screenWidth - 120, 10, 60, 12);

    } else if ((stats.state == CANCELADA) || (stats.state == TERMINADA)) {
        text += "GAME OVER - PRESS Q OR CLOSE THE WINDOW TO RETURN TO THE LOBBY";
        destRect = SDL2pp::Rect(screenWidth/2 - 180, 10, 390, 12);

    } else if (stats.state == PAUSADA) {
        const PlayerStatDto* firstPlayerStats = stats.getPlayerStat(static_cast<int>(stats.champion_player));

        if (firstPlayerStats != nullptr) {
            if (firstPlayerStats->wins  < context.wins_needed) {
                int winsNeeded = context.wins_needed - firstPlayerStats->wins;
                text += "ROUND BREAK - PLAYER " + std::to_string(stats.champion_player) + " NEEDS " + std::to_string(winsNeeded) + " MORE WINS";
            } else {
                text += "THERE'S A TIE -  " + std::to_string(context.rounds_per_set) + " MORE ROUNDS TO PLAY";
            }
        } else {
            text += "THERE'S A TIE - " + std::to_string(context.rounds_per_set) + " MORE ROUNDS TO PLAY";
        }

        destRect = SDL2pp::Rect(screenWidth/2 - 180, 10, 390, 12);

    } else if (stats.state == ROUND_END) {
        text += "PLAYER " + std::to_string(stats.champion_player) + " WON ROUND " + std::to_string(stats.numronda);
        destRect = SDL2pp::Rect(screenWidth - 200, 10, 170, 12);

    }

    SDL2pp::Texture text_sprite(renderer, font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));

	renderer.Copy(text_sprite, SDL2pp::NullOpt, destRect);
}

void Drawer::drawLeaderboardBackground(double scaleX, double scaleY) {
    int leaderboardX = static_cast<int>(50 * scaleX);
    int leaderboardY = static_cast<int>(50 * scaleY);
    int leaderboardWidth = static_cast<int>(520 * scaleX);
    int leaderboardHeight = static_cast<int>(400 * scaleY);

    renderer.Copy(
        textures.getTexture("/leaderboard/emptyScoreboard.png"),
        SDL2pp::Rect(0, 0, 320, 200),
        SDL2pp::Rect(leaderboardX, leaderboardY, leaderboardWidth, leaderboardHeight)
    );
}

void Drawer::drawTrophy(double scaleX, double scaleY) {
    int trophyX = static_cast<int>(350 * scaleX);
    int trophyY = static_cast<int>(125 * scaleY);
    int trophySize = static_cast<int>(32 * scaleX);

    renderer.Copy(
        textures.getTexture("/leaderboard/trophy.png"),
        SDL2pp::Rect(0, 0, 17, 20),
        SDL2pp::Rect(trophyX, trophyY + 15, trophySize, trophySize)
    );
}

void Drawer::drawPlayerStats(const MatchStatsInfo& matchStats, double scaleX, double scaleY) {
    std::vector<PlayerStatDto> sortedStats = matchStats.stats;
    std::sort(sortedStats.begin(), sortedStats.end(),
              [](const PlayerStatDto& a, const PlayerStatDto& b) { return a.wins > b.wins; });

    int y = static_cast<int>(125 * scaleY);
    int rowSpacing = static_cast<int>(50 * scaleY);
    for (const PlayerStatDto& playerStat : sortedStats) {
        playerDrawer.drawStats(playerStat, scaleX, scaleY, y, rowSpacing);        
    }
}

void Drawer::draw(const MatchDto& matchDto, const MatchStatsInfo& stats) {
    renderer.Clear();

    backgroundDrawer.draw(window.GetWidth(), window.GetHeight());

    backgroundDrawer.drawObjects(matchDto);

    playerDrawer.updateIndicatorFlag();

    drawStatusBar(stats);

    for (const PlayerDTO& player: matchDto.players) {

        if (playerDrawer.getIndicatorFlag()) {
            if (player.id == context.first_player) {
                playerDrawer.drawIndicator(player, IS_MAIN_PLAYER);
            } else if ((context.dualplay) && (player.id == context.second_player)) {
                playerDrawer.drawIndicator(player, IS_SECONDARY_PLAYER);
            }
        }

        playerDrawer.draw(player);
    }

    backgroundDrawer.drawExplosions();

    // Show rendered frame
    renderer.Present();
}

void Drawer::drawLeaderboard(const MatchStatsInfo& matchStats) {
    int screenWidth = window.GetWidth();
    int screenHeight = window.GetHeight();

    double scaleX = static_cast<double>(screenWidth) / INITIAL_SCREEN_WIDTH;
    double scaleY = static_cast<double>(screenHeight) / INITIAL_SCREEN_HEIGHT;

    renderer.Clear();

    backgroundDrawer.draw(screenWidth, screenHeight);

    drawStatusBar(matchStats);

    drawLeaderboardBackground(scaleX, scaleY);

    if (matchStats.state == TERMINADA) {
        drawTrophy(scaleX, scaleY);
    }

    drawPlayerStats(matchStats, scaleX, scaleY);

    renderer.Present();
}

void Drawer::drawWinner(const MatchStatsInfo& matchStats, const MatchDto& matchDto) {
    renderer.Clear();

    backgroundDrawer.draw(window.GetWidth(), window.GetHeight());

    backgroundDrawer.drawObjects(matchDto);

    drawStatusBar(matchStats);

    const PlayerDTO* winner = matchDto.getPlayer((int)matchStats.champion_player);

    playerDrawer.draw(*winner);

    int playerX = camera.getScreenX(winner->pos.x);
    int playerY = camera.getScreenY(winner->pos.y);
    SDL2pp::Texture& texture = textures.getTexture("/font/biosFont.png");

    renderer.Copy(texture, SDL2pp::Rect(88, 0, 8, 8),
                  SDL2pp::Rect(playerX + 15, playerY - 32, 24, 24));
    renderer.Copy(texture, SDL2pp::Rect(8, 8, 8, 8),
                  SDL2pp::Rect(playerX + 35, playerY - 32, 24, 24));

    // Show rendered frame
    renderer.Present();
}

Drawer::~Drawer() = default;
