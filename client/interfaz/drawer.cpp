#include "drawer.h"

Drawer::Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
               Camera& camera):
        window(window),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textures(renderer),
        animation(animation),
        camera(camera),
        context(gameContext),
        startTime(std::chrono::steady_clock::now()),
        showIndicators(true) {

    duckTextures = {{1, "/duck_sprites/duck_white.png"},
                    {2, "/duck_sprites/duck_yellow.png"},
                    {3, "/duck_sprites/duck_grey.png"},
                    {4, "/duck_sprites/duck_orange.png"}};
    weaponTextures = {{TypeWeapon::PISTOLA_COWBOY,
                       {"/weapons/cowboyPistol.png", COWBOY_GUN_WIDTH, COWBOY_GUN_HEIGHT}},
                      {TypeWeapon::PEW_PEW_LASER,
                       {"/weapons/pewpewLaser.png", PEW_PEW_LASER_SIZE, PEW_PEW_LASER_SIZE}},
                      {TypeWeapon::MAGNUM, {"/weapons/magnum.png", MAGNUM_SIZE, MAGNUM_SIZE}}};
}

void Drawer::drawPlayer(const PlayerDTO& player) {
    const std::string playerTexture;
    auto mappedTexture = duckTextures.find(player.id);
    if (mappedTexture != duckTextures.end()) {
        const auto& playerTexture = mappedTexture->second;

        SDL_RendererFlip flip =
                animation.isFacingLeft(player.id) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        renderer.Copy(
                textures.getTexture(playerTexture),
                SDL2pp::Rect(animation.getSpriteX(player.id), animation.getSpriteY(player.id),
                             SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(camera.getScreenX(player.pos.x - X_PHYSICAL_OFFSET_PLAYER),
                             camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER - 16),
                             camera.getScaledSize(SPRITE_SIZE), camera.getScaledSize(SPRITE_SIZE)),
                0.0, SDL2pp::Point(0, 0), flip);

        if (player.weapon != TypeWeapon::NONE) {
            drawWeapon(player, flip);
        }

        drawArmor(player, flip);

        drawPlayerInfo(player, playerTexture);
    }
}

void Drawer::drawPlayerInfo(const PlayerDTO& player, const std::string color) {
    renderer.Copy(textures.getTexture(color), SDL2pp::Rect(1, 10, 32, 10),
                  SDL2pp::Rect(4 + 90 * (player.id - 1), 8, 32, 14));

    if (player.weapon != TypeWeapon::NONE) {
        auto weaponTexture = weaponTextures.find(player.weapon);
        if (weaponTexture != weaponTextures.end()) {
            const auto& [textureType, width, height] = weaponTexture->second;

            int x, y;
            if (player.weapon == TypeWeapon::PISTOLA_COWBOY) {
                x = 30;
                y = 2;
            } else {
                x = 22;
                y = -3;
            }

            renderer.Copy(textures.getTexture(textureType), SDL2pp::Rect(0, 0, width, height),
                          SDL2pp::Rect(x + 90 * (player.id - 1), y, width, height));
        }
    } else {
        renderer.Copy(textures.getTexture("/ui/iconSheet.png"), SDL2pp::Rect(32, 16, 16, 16),
                      SDL2pp::Rect(40 + 90 * (player.id - 1), 6, 16, 16));
    }

    if (!player.helmet) {
        renderer.Copy(textures.getTexture("/ui/iconSheet.png"), SDL2pp::Rect(32, 16, 16, 16),
                      SDL2pp::Rect(57 + 90 * (player.id - 1), 6, 16, 16));
    } else {
        renderer.Copy(textures.getTexture("/armors/helmetPickup.png"), SDL2pp::Rect(0, 0, 16, 16),
                      SDL2pp::Rect(52 + 90 * (player.id - 1), 3, 16, 16));
    }

    if (!player.chest_armor) {
        renderer.Copy(textures.getTexture("/ui/iconSheet.png"), SDL2pp::Rect(32, 16, 16, 16),
                      SDL2pp::Rect(73 + 90 * (player.id - 1), 6, 16, 16));
    } else {
        renderer.Copy(textures.getTexture("/armors/chestPlatePickup.png"),
                      SDL2pp::Rect(0, 0, 16, 16),
                      SDL2pp::Rect(68 + 90 * (player.id - 1), 6, 16, 16));
    }
}

void Drawer::drawIndicator(const PlayerDTO& player, bool isMainPlayer) {
    SDL2pp::Rect indicatorType;

    float spriteX = animation.getIndicatorSprite(INDICATOR_WIDTH);

    if (isMainPlayer) {
        indicatorType = SDL2pp::Rect(spriteX, 0, INDICATOR_WIDTH, INDICATOR_HEIGHT);
    } else {
        indicatorType = SDL2pp::Rect(spriteX, INDICATOR_HEIGHT, INDICATOR_WIDTH, INDICATOR_HEIGHT);
    }

    renderer.Copy(textures.getTexture(TextureContainer::PLAYER_INDICATOR), indicatorType,
                  SDL2pp::Rect(camera.getScreenX(player.pos.x - X_PHYSICAL_OFFSET_PLAYER + 9),
                               camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER - 40),
                               camera.getScaledSize(INDICATOR_WIDTH_RESIZED),
                               camera.getScaledSize(INDICATOR_HEIGHT_RESIZED)));
}

void Drawer::drawArmor(const PlayerDTO& player, SDL_RendererFlip flip) {

    if (player.helmet) {
        renderer.Copy(
                textures.getTexture(TextureContainer::HELMET_ARMOR),
                SDL2pp::Rect(0, 0, SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(
                        camera.getScreenX(player.pos.x + getTextureFlipValue(flip, HELMET_FLIP_X,
                                                                             HELMET_UNFLIP_X)),
                        camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER - 10),
                        camera.getScaledSize(SPRITE_SIZE), camera.getScaledSize(SPRITE_SIZE)),
                0.0, SDL2pp::Point(0, 0), flip);
    }


    if (player.chest_armor) {
        renderer.Copy(
                textures.getTexture(TextureContainer::CHEST_ARMOR),
                SDL2pp::Rect(0, 0, SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(camera.getScreenX(player.pos.x),
                             camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER + 3),
                             camera.getScaledSize(SPRITE_SIZE), camera.getScaledSize(SPRITE_SIZE)),
                0.0, SDL2pp::Point(0, 0), flip);
    }
}

void Drawer::drawWeapon(const PlayerDTO& player, SDL_RendererFlip flip) {
    auto weaponTexture = weaponTextures.find(player.weapon);
    if (weaponTexture != weaponTextures.end()) {
        const auto& [textureType, width, height] = weaponTexture->second;

        int x, y;  // ajusto medidas de dibujado
        if (player.weapon == TypeWeapon::PISTOLA_COWBOY) {
            x = camera.getScreenX(player.pos.x +
                                  getTextureFlipValue(flip, GUN_FLIP_X, GUN_UNFLIP_X) -
                                  X_PHYSICAL_OFFSET_PLAYER);
            y = camera.getScreenY(player.pos.y + 4);
        } else {
            x = camera.getScreenX(player.pos.x - X_PHYSICAL_OFFSET_PLAYER +
                                  getTextureFlipValue(flip, -3, 9));
            y = camera.getScreenY(player.pos.y - 6);
        }

        renderer.Copy(textures.getTexture(textureType), SDL2pp::Rect(0, 0, width, height),
                      SDL2pp::Rect(x, y, camera.getScaledSize(width - 6),
                                   camera.getScaledSize(height - 6)),
                      0.0, SDL2pp::Point(0, 0), flip);
    }
}

int Drawer::getTextureFlipValue(SDL_RendererFlip flip, int flipValue, int unflipValue) {
    return flip == SDL_FLIP_HORIZONTAL ? flipValue : unflipValue;
}

void Drawer::drawBackground() {
    const float PARALLAX_OFFSET_FACTOR = 0.5f;
    int windowWidth = window.GetWidth();
    int windowHeight = window.GetHeight();

    SDL_Rect visibleSection =
            camera.backgroundVisibleSection(windowWidth, windowHeight, PARALLAX_OFFSET_FACTOR);

    renderer.Copy(
            textures.getTexture(context.map.background),
            SDL2pp::Rect(visibleSection.x, visibleSection.y, visibleSection.w, visibleSection.h),
            SDL2pp::Rect(0, 0, windowWidth, windowHeight));
}

void Drawer::drawObjects(const MatchDto& matchDto) {
    for (const MapObject& object: context.map.objects) {
        drawMapObject(object);
    }

    for (const DynamicObjDTO& object: matchDto.objects) {
        drawDynamicObject(object);
    }
}

void Drawer::drawMapObject(const MapObject& object) {
    renderer.Copy(
            textures.getTexture(object.texture), SDL2pp::Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT),
            SDL2pp::Rect(camera.getScreenX(object.column * BLOCK_WIDTH),
                         camera.getScreenY(-object.row * BLOCK_HEIGHT),
                         camera.getScaledSize(BLOCK_WIDTH), camera.getScaledSize(BLOCK_HEIGHT)));
}

void Drawer::drawDynamicObject(const DynamicObjDTO& object) {
    switch (object.type) {
        case TypeDynamicObject::BOX:
            renderer.Copy(
                    textures.getTexture(context.map.boxes_tex),
                    SDL2pp::Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(BLOCK_WIDTH),
                                 camera.getScaledSize(BLOCK_HEIGHT)));
            break;

        case TypeDynamicObject::PROJECTILE:
            renderer.Copy(
                    textures.getTexture("/weapons/chainBullet.png"), SDL2pp::Rect(0, 0, 3, 8),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(object.pos.y),
                                 camera.getScaledSize(3), camera.getScaledSize(8)));
            break;

        case TypeDynamicObject::LASER:
            renderer.Copy(
                    textures.getTexture("/weapons/laserBeam.png"), SDL2pp::Rect(0, 0, 1, 8),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(1), camera.getScaledSize(8)));
            break;

        case TypeDynamicObject::BURST:
            // dibujado del burst, no lo encontre en res
            renderer.Copy(
                    textures.getTexture("/notexture.png"),
                    SDL2pp::Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(BLOCK_WIDTH),
                                 camera.getScaledSize(BLOCK_HEIGHT)));
            break;

        case TypeDynamicObject::HELMET:
            renderer.Copy(
                    textures.getTexture("/armors/helmetPickup.png"), SDL2pp::Rect(0, 0, 16, 16),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(16), camera.getScaledSize(16)));
            break;

        case TypeDynamicObject::ARMOR:
            renderer.Copy(
                    textures.getTexture("/armors/chestPlatePickup.png"), SDL2pp::Rect(0, 0, 16, 16),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(16), camera.getScaledSize(16)));
            break;

        case TypeDynamicObject::GRANADA:
            renderer.Copy(
                    textures.getTexture("/weapons/grenade.png"), SDL2pp::Rect(0, 0, 16, 16),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(16), camera.getScaledSize(16)));
            break;

        case TypeDynamicObject::BANANA:
            renderer.Copy(
                    textures.getTexture("/weapons/banana.png"), SDL2pp::Rect(0, 0, 16, 16),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(16), camera.getScaledSize(16)));
            break;

        case TypeDynamicObject::PEW_PEW_LASER:
            renderer.Copy(
                    textures.getTexture("/weapons/pewpewLaser.png"),
                    SDL2pp::Rect(0, 0, PEW_PEW_LASER_SIZE, PEW_PEW_LASER_SIZE),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(PEW_PEW_LASER_SIZE),
                                 camera.getScaledSize(PEW_PEW_LASER_SIZE)));
            break;

        case TypeDynamicObject::LASER_RIFLE:
            renderer.Copy(
                    textures.getTexture("/weapons/laserRifle.png"), SDL2pp::Rect(0, 0, 32, 32),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(32), camera.getScaledSize(32)));
            break;

        case TypeDynamicObject::AK_47:
            renderer.Copy(
                    textures.getTexture("/weapons/ak47.png"), SDL2pp::Rect(0, 0, 32, 32),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(32), camera.getScaledSize(32)));
            break;

        case TypeDynamicObject::PISTOLA_DE_DUELOS:
            renderer.Copy(
                    textures.getTexture("/weapons/pistol.png"), SDL2pp::Rect(0, 0, 18, 18),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(18), camera.getScaledSize(18)));
            break;

        case TypeDynamicObject::PISTOLA_COWBOY:
            renderer.Copy(
                    textures.getTexture("/weapons/cowboyPistol.png"),
                    SDL2pp::Rect(0, 0, COWBOY_GUN_WIDTH, COWBOY_GUN_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(COWBOY_GUN_WIDTH - 6),
                                 camera.getScaledSize(COWBOY_GUN_HEIGHT - 6)));
            break;

        case TypeDynamicObject::MAGNUM:
            renderer.Copy(
                    textures.getTexture("/weapons/magnum.png"),
                    SDL2pp::Rect(0, 0, MAGNUM_SIZE, MAGNUM_SIZE),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(MAGNUM_SIZE),
                                 camera.getScaledSize(MAGNUM_SIZE)));
            break;

        case TypeDynamicObject::ESCOPETA:
            renderer.Copy(
                    textures.getTexture("/weapons/shotgun.png"), SDL2pp::Rect(0, 0, 32, 32),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(32), camera.getScaledSize(32)));
            break;

        case TypeDynamicObject::SNIPER:
            renderer.Copy(
                    textures.getTexture("/weapons/sniper.png"), SDL2pp::Rect(0, 0, 33, 9),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(33), camera.getScaledSize(9)));
            break;

        default:
            renderer.Copy(
                    textures.getTexture("/notexture.png"),
                    SDL2pp::Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(BLOCK_WIDTH),
                                 camera.getScaledSize(BLOCK_HEIGHT)));
            break;
    }
}

void Drawer::updateIndicatorFlag() {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime =
            std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    showIndicators = elapsedTime < INDICATOR_MAX_TIME;
}

void Drawer::resetIndicatorFlag() {
    startTime = std::chrono::steady_clock::now();
    showIndicators = true;
}

void Drawer::drawStatusBar() {
    renderer.Copy(textures.getTexture("/ui/statusBar.png"), SDL2pp::Rect(0, 0, 260, 13),
                  SDL2pp::Rect(0, 0, window.GetWidth(), 30));
}

void Drawer::draw(const MatchDto& matchDto) {
    renderer.Clear();

    drawBackground();

    drawObjects(matchDto);

    updateIndicatorFlag();

    drawStatusBar();

    for (const PlayerDTO& player: matchDto.players) {

        if (showIndicators) {
            if (player.id == context.first_player) {
                drawIndicator(player, IS_MAIN_PLAYER);
            } else if ((context.dualplay) && (player.id == context.second_player)) {
                drawIndicator(player, IS_SECONDARY_PLAYER);
            }
        }

        drawPlayer(player);
    }

    // Show rendered frame
    renderer.Present();
}

void Drawer::drawLeaderboard(const MatchStatsInfo& matchStats) {
    renderer.Clear();

    drawBackground();

    renderer.Copy(textures.getTexture("/leaderboard/emptyScoreboard.png"),
                  SDL2pp::Rect(0, 0, 320, 200), SDL2pp::Rect(50, 50, 520, 400));

    int y = 125;

    if (matchStats.state == TERMINADA) {
        renderer.Copy(textures.getTexture("/leaderboard/trophy.png"), SDL2pp::Rect(0, 0, 17, 20),
                      SDL2pp::Rect(350, y + 15, 32, 32));
    }

    // ordenar el vector en orden ascendiente
    std::vector<PlayerStatDto> sortedStats = matchStats.stats;
    std::sort(sortedStats.begin(), sortedStats.end(),
              [](const PlayerStatDto& a, const PlayerStatDto& b) { return a.wins > b.wins; });

    for (const PlayerStatDto& playerStat: sortedStats) {
        auto mappedTexture = duckTextures.find(static_cast<int>(playerStat.id));
        if (mappedTexture != duckTextures.end()) {
            const auto& playerTexture = mappedTexture->second;

            renderer.Copy(  // jugador
                    textures.getTexture(playerTexture),
                    SDL2pp::Rect(1, 10, SPRITE_SIZE, SPRITE_SIZE), SDL2pp::Rect(165, y, 64, 64));

            renderer.Copy(  // rondas ganadas
                    textures.getTexture(TextureContainer::FONT),
                    SDL2pp::Rect(8 * (static_cast<int>(playerStat.wins)), 8, 8, 8),
                    SDL2pp::Rect(250, y + 15, 20, 20));
        }

        y += 50;
    }

    // Show rendered frame
    renderer.Present();
}

void Drawer::drawWinner(const MatchStatsInfo& matchStats, const MatchDto& matchDto) {
    renderer.Clear();

    drawBackground();

    drawObjects(matchDto);

    drawStatusBar();

    const PlayerDTO* winner = matchDto.getPlayer((int)matchStats.champion_player);

    drawPlayer(*winner);

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
