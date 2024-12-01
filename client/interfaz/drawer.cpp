#include "drawer.h"

Drawer::Drawer(SDL2pp::Window& window, Animation& animation, const GameContext& gameContext,
               Camera& camera):
        font(DATA_PATH "/font/pixelFont.ttf", 20),
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
                      {TypeWeapon::MAGNUM, {"/weapons/magnum.png", MAGNUM_SIZE, MAGNUM_SIZE}},
                      {TypeWeapon::PISTOLA_DE_DUELOS, {"/weapons/pistol.png", PISTOL_SIZE, PISTOL_SIZE}},
                      {TypeWeapon::ESCOPETA, {"/weapons/shotgun.png", SHOTGUN_SIZE, SHOTGUN_SIZE}},
                      {TypeWeapon::SNIPER, {"/weapons/sniper.png", SNIPER_WIDTH, SNIPER_HEIGHT}},
                      {TypeWeapon::AK_47, {"/weapons/ak47.png", AK47_SIZE, AK47_SIZE}},
                      {TypeWeapon::LASER_RIFLE, {"/weapons/laserRifle.png", LASER_RIFLE_SIZE, LASER_RIFLE_SIZE}},
                      {TypeWeapon::GRANADA, {"/weapons/grenade.png", GRENADE_SIZE, GRENADE_SIZE}},
                      {TypeWeapon::BANANA, {"/weapons/banana.png", BANANA_SIZE, BANANA_SIZE}}};
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

        drawArmor(player, flip);

        if (player.weapon != TypeWeapon::NONE) {
            drawWeapon(player, flip);
        }

        if (player.is_alive) {
            drawPlayerInfo(player, playerTexture);
        }
    }
}

void Drawer::drawPlayerInfo(const PlayerDTO& player, const std::string color) {
    renderer.Copy(textures.getTexture(color), SDL2pp::Rect(1, 10, 32, 10),
                  SDL2pp::Rect(12 + 115 * (player.id - 1), 8, 32, 14));
    
    int health;
    if (player.hp > 3) {
        health = 16;
    } else {
        health = (5 * player.hp) + 1;
    }
    
    renderer.Copy(textures.getTexture("/ui/hp.png"), SDL2pp::Rect(0, 0, health, 16),
                        SDL2pp::Rect(35 + 115 * (player.id - 1), 5, health, 20));

    if (player.weapon != TypeWeapon::NONE) {
        auto weaponTexture = weaponTextures.find(player.weapon);
        if (weaponTexture != weaponTextures.end()) {
            const auto& [textureType, width, height] = weaponTexture->second;

            int x, y;
            if (player.weapon == TypeWeapon::PISTOLA_COWBOY || player.weapon == TypeWeapon::SNIPER) {
                x = 60;
                y = 7;
            } else if (player.weapon == TypeWeapon::GRANADA) {
                x = 65;
                y = 7;
            } else {
                x = 54;
                y = -3;
            }

            renderer.Copy(textures.getTexture(textureType), SDL2pp::Rect(0, 0, width, height),
                          SDL2pp::Rect(x + 115 * (player.id - 1), y, width, height));
            
            std::string text = std::to_string(player.munition);
            SDL2pp::Texture text_sprite(renderer, font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));

            renderer.Copy(text_sprite, SDL2pp::NullOpt,
                        SDL2pp::Rect(x + 45 + 115 * (player.id - 1), 9, 12, 12));
        }
    }

    if (player.helmet) {
        renderer.Copy(textures.getTexture("/armors/helmet.png"), SDL2pp::Rect(0, 0, 32, 32),
                      SDL2pp::Rect(8 + 115 * (player.id - 1), -9, 32, 32));
    }

    if (player.chest_armor) {
        renderer.Copy(textures.getTexture("/armors/chestPlateAnim.png"),
                      SDL2pp::Rect(0, 0, 32, 16),
                      SDL2pp::Rect(10 + 115 * (player.id - 1), -6, 32, 32));
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

    renderer.Copy(textures.getTexture("/duck_sprites/playerIndicator.png"), indicatorType,
                  SDL2pp::Rect(camera.getScreenX(player.pos.x - X_PHYSICAL_OFFSET_PLAYER + 9),
                               camera.getScreenY(player.pos.y + Y_PHYSICAL_OFFSET_PLAYER - 40),
                               camera.getScaledSize(INDICATOR_WIDTH_RESIZED),
                               camera.getScaledSize(INDICATOR_HEIGHT_RESIZED)));
}

void Drawer::getArmorParameters(const PlayerDTO& player, SDL_RendererFlip flip, int& chestArmorX, int& chestArmorY, int& helmetArmorX, int& helmetArmorY, float& angle) {
    if (player.move_action == TypeMoveAction::STAY_DOWN) {
        angle = getTextureFlipValue(flip, 90.0, -90.0);
        chestArmorX = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, 21, -5));
        chestArmorY = camera.getScreenY(player.pos.y + getTextureFlipValue(flip, -4, 24));
        helmetArmorX = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, 34, -19));
        helmetArmorY = camera.getScreenY(player.pos.y + getTextureFlipValue(flip, -1, 27));
    } else {
        if (player.move_action == TypeMoveAction::FLAP_LEFT || player.move_action == TypeMoveAction::FLAP_RIGHT || player.move_action == TypeMoveAction::FLAP_NEUTRAL) {
            helmetArmorY = camera.getScreenY(player.pos.y - 16);
            chestArmorY = camera.getScreenY(player.pos.y - 3);
        } else {
            chestArmorY = camera.getScreenY(player.pos.y - 7);
            helmetArmorY = camera.getScreenY(player.pos.y - 20);
        }
        chestArmorX = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, -7, -6));
        helmetArmorX = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, -3, -9));
    }
}

void Drawer::drawArmor(const PlayerDTO& player, SDL_RendererFlip flip) {
    int chestArmorX, chestArmorY, helmetArmorX, helmetArmorY;
    float angle = 0.0;
    
    getArmorParameters(player, flip, chestArmorX, chestArmorY, helmetArmorX, helmetArmorY, angle);

    if (player.helmet) {
        renderer.Copy(
                textures.getTexture("/armors/helmet.png"),
                SDL2pp::Rect(0, 0, SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(helmetArmorX, helmetArmorY,
                        camera.getScaledSize(SPRITE_SIZE -3), camera.getScaledSize(SPRITE_SIZE-3)),
                angle, SDL2pp::Point(0, 0), flip);
    }


    if (player.chest_armor) {
        renderer.Copy(
                textures.getTexture("/armors/chestPlateAnim.png"),
                SDL2pp::Rect(0, 0, SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(chestArmorX, chestArmorY,
                             camera.getScaledSize(SPRITE_SIZE-3), camera.getScaledSize(SPRITE_SIZE-3)),
                angle, SDL2pp::Point(0, 0), flip);
    }
}

void Drawer::getWeaponParameters(const PlayerDTO& player, SDL_RendererFlip flip, int& x, int& y, double& angle, int& sizeAdjustment) {
    if (player.weapon == TypeWeapon::PISTOLA_COWBOY || player.weapon == TypeWeapon::GRANADA) {
        if (player.aiming_up) {
            angle = getTextureFlipValue(flip, 90.0, -90.0);
            x = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, 21, 14) - 8);
            y = camera.getScreenY(player.pos.y + getTextureFlipValue(flip, -12, 6));
        } else {
            angle = 0.0;
            x = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, 1, 14) - 8);
            y = camera.getScreenY(player.pos.y + 2);
        }
        sizeAdjustment = 3;
    } else if (player.weapon == TypeWeapon::SNIPER) {
        if (player.aiming_up) {
            angle = getTextureFlipValue(flip, 90.0, -90.0);
            x = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, 20, 14) - 8);
            y = camera.getScreenY(player.pos.y + getTextureFlipValue(flip, -24, 6));
        } else {
            angle = 0.0;
            x = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, -10, 8) - 8);
            y = camera.getScreenY(player.pos.y + 2);
        }
        sizeAdjustment = 0;
    } else {
        if (player.aiming_up) {
            angle = getTextureFlipValue(flip, 90.0, -90.0);
            x = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, 28, 2) - 8);
            y = camera.getScreenY(player.pos.y + getTextureFlipValue(flip, -15, 10));
        } else {
            angle = 0.0;
            x = camera.getScreenX(player.pos.x - 8 + getTextureFlipValue(flip, -3, 9));
            y = camera.getScreenY(player.pos.y - 6);
        }
        sizeAdjustment = 6;
    }
}

void Drawer::getShotExplosionParameters(const PlayerDTO& player, SDL_RendererFlip flip, int x, int y, int& explosionX, int& explosionY) {
    if (player.weapon == TypeWeapon::PISTOLA_COWBOY) {
        if (player.aiming_up) {
            explosionX = x + getTextureFlipValue(flip, 8, -8);
            explosionY = y + getTextureFlipValue(flip, -20, -30);
        } else {
            explosionX = x + getTextureFlipValue(flip, -20, 30);
            explosionY = y - 8;
        }
    } else if (player.weapon == TypeWeapon::PEW_PEW_LASER) {
        if (player.aiming_up) {
            explosionX = x + getTextureFlipValue(flip, -6, 6);
            explosionY = y + getTextureFlipValue(flip, -25, -45);
        } else {
            explosionX = x + getTextureFlipValue(flip, -15, 50);
            explosionY = y + 8;
        }
    } else if (player.weapon == TypeWeapon::ESCOPETA || player.weapon == TypeWeapon::AK_47) {
        if (player.aiming_up) {
            explosionX = x + getTextureFlipValue(flip, -12, 14);
            explosionY = y + getTextureFlipValue(flip, -25, -57);
        } else {
            explosionX = x + getTextureFlipValue(flip, -25, 56);
            explosionY = y + 12;
        }
    } else if (player.weapon == TypeWeapon::SNIPER) {
        if (player.aiming_up) {
            explosionX = x + getTextureFlipValue(flip, 3, -4);
            explosionY = y + getTextureFlipValue(flip, -25, -68);
        } else {
            explosionX = x + getTextureFlipValue(flip, -27, 65);
            explosionY = y - 4;
        }
    } else if (player.weapon == TypeWeapon::LASER_RIFLE) {
        if (player.aiming_up) {
            explosionX = x + getTextureFlipValue(flip, 10, -8);
            explosionY = y + getTextureFlipValue(flip, -60, -45);
        } else {
            explosionX = x + getTextureFlipValue(flip, -55, 45);
            explosionY = y - 10;
        }
    } else {
        if (player.aiming_up) {
            explosionX = x + getTextureFlipValue(flip, -8, 8);
            explosionY = y + getTextureFlipValue(flip, -15, -42);
        } else {
            explosionX = x + getTextureFlipValue(flip, -12, 43);
            explosionY = y + 8;
        }
    }
}

void Drawer::drawWeapon(const PlayerDTO& player, SDL_RendererFlip flip) {
    auto weaponTexture = weaponTextures.find(player.weapon);
    if (weaponTexture != weaponTextures.end()) {
        const auto& [textureType, width, height] = weaponTexture->second;

        int x, y, sizeAdjustment;
        double angle;

        getWeaponParameters(player, flip, x, y, angle, sizeAdjustment);

        renderer.Copy(
            textures.getTexture(textureType), 
            SDL2pp::Rect(0, 0, width, height),
            SDL2pp::Rect(x, y, camera.getScaledSize(width - sizeAdjustment), camera.getScaledSize(height - sizeAdjustment)),
            angle, SDL2pp::Point(0, 0), flip
        );

        for (const ExplosionAnimation& explosion : animation.getExplosions(player.id)) {
            int explosionX, explosionY;
            int size = explosion.getSpriteSize();
            
            getShotExplosionParameters(player, flip, x, y, explosionX, explosionY);
            
            renderer.Copy(
                textures.getTexture(explosion.getTexture()),
                SDL2pp::Rect(explosion.getCurrentFrame() * size, 0, size, size),
                SDL2pp::Rect(explosionX, explosionY, camera.getScaledSize(size), camera.getScaledSize(size)),
                angle, SDL2pp::Point(0, 0), flip);
        }
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
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y + 10),
                                 camera.getScaledSize(3), camera.getScaledSize(8)));
            break;

        case TypeDynamicObject::LASER:
            renderer.Copy(
                    textures.getTexture("/weapons/laserBeam.png"), SDL2pp::Rect(0, 0, 1, 8),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y + 10),
                                 camera.getScaledSize(1), camera.getScaledSize(8)));
            break;
        
        case TypeDynamicObject::LASER_2:
            renderer.Copy(
                    textures.getTexture("/weapons/yellowLaser.png"), SDL2pp::Rect(0, 0, 1, 5),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y + 10),
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

        case TypeDynamicObject::GRENADE_PROJECTILE:
            renderer.Copy(
                    textures.getTexture("/weapons/grenadePin.png"), SDL2pp::Rect(0, 0, 16, 16),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(16), camera.getScaledSize(16)));
            break;

        case TypeDynamicObject::GRANADA:
            renderer.Copy(
                    textures.getTexture("/weapons/grenade.png"), SDL2pp::Rect(0, 0, GRENADE_SIZE, GRENADE_SIZE),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(GRENADE_SIZE), camera.getScaledSize(GRENADE_SIZE)));
            break;

        case TypeDynamicObject::BANANA:
            renderer.Copy(
                    textures.getTexture("/weapons/banana.png"), SDL2pp::Rect(0, 0, BANANA_SIZE, BANANA_SIZE),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(BANANA_SIZE), camera.getScaledSize(BANANA_SIZE)));
            break;

        case TypeDynamicObject::PEW_PEW_LASER:
            renderer.Copy(
                    textures.getTexture("/weapons/pewpewLaser.png"),
                    SDL2pp::Rect(0, 0, PEW_PEW_LASER_SIZE, PEW_PEW_LASER_SIZE),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x - 3), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(PEW_PEW_LASER_SIZE - 6),
                                 camera.getScaledSize(PEW_PEW_LASER_SIZE - 6)));
            break;

        case TypeDynamicObject::LASER_RIFLE:
            renderer.Copy(
                    textures.getTexture("/weapons/laserRifle.png"), SDL2pp::Rect(0, 0, LASER_RIFLE_SIZE, LASER_RIFLE_SIZE),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x - 3), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(LASER_RIFLE_SIZE - 6), camera.getScaledSize(LASER_RIFLE_SIZE - 6)));
            break;

        case TypeDynamicObject::AK_47:
            renderer.Copy(
                    textures.getTexture("/weapons/ak47.png"), SDL2pp::Rect(0, 0, AK47_SIZE, AK47_SIZE),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x - 3), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(AK47_SIZE - 6), camera.getScaledSize(AK47_SIZE - 6)));
            break;

        //case TypeDynamicObject::PISTOLA_DE_DUELOS:
            //renderer.Copy(textures.getTexture("/weapons/pistol.png"), SDL2pp::Rect(0, 0, 18, 18), SDL2pp::Rect(camera.getScreenX(object.pos.x), camera.getScreenY(-object.pos.y), camera.getScaledSize(18 - 4), camera.getScaledSize(18 - 4)));
            //break;

        case TypeDynamicObject::PISTOLA_COWBOY:
            renderer.Copy(
                    textures.getTexture("/weapons/cowboyPistol.png"),
                    SDL2pp::Rect(0, 0, COWBOY_GUN_WIDTH, COWBOY_GUN_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x + 3), camera.getScreenY(-object.pos.y + 5),
                                 camera.getScaledSize(COWBOY_GUN_WIDTH - 3),
                                 camera.getScaledSize(COWBOY_GUN_HEIGHT - 3)));
            break;
        
        case TypeDynamicObject::PISTOLA_DE_DUELOS:
        case TypeDynamicObject::MAGNUM:
            renderer.Copy(
                    textures.getTexture("/weapons/magnum.png"),
                    SDL2pp::Rect(0, 0, MAGNUM_SIZE, MAGNUM_SIZE),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x - 3), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(MAGNUM_SIZE - 6),
                                 camera.getScaledSize(MAGNUM_SIZE - 6)));
            break;

        case TypeDynamicObject::ESCOPETA:
            renderer.Copy(
                    textures.getTexture("/weapons/shotgun.png"), SDL2pp::Rect(0, 0, SHOTGUN_SIZE, SHOTGUN_SIZE),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x - 3), camera.getScreenY(-object.pos.y),
                                 camera.getScaledSize(SHOTGUN_SIZE - 6), camera.getScaledSize(SHOTGUN_SIZE - 6)));
            break;

        case TypeDynamicObject::SNIPER:
            renderer.Copy(
                    textures.getTexture("/weapons/sniper.png"), SDL2pp::Rect(0, 0, SNIPER_WIDTH, SNIPER_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x - 5), camera.getScreenY(-object.pos.y + 10),
                                 camera.getScaledSize(SNIPER_WIDTH), camera.getScaledSize(SNIPER_HEIGHT)));
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
        text += "THERE'S A TIE, 5 MORE ROUNDS TO PLAY";
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
        auto mappedTexture = duckTextures.find(static_cast<int>(playerStat.id));
        if (mappedTexture != duckTextures.end()) {
            const auto& playerTexture = mappedTexture->second;

            int playerSpriteX = static_cast<int>(165 * scaleX);
            int playerSpriteSizeWidth = static_cast<int>(64 * scaleX);
            int playerSpriteSizeHeight = static_cast<int>(64 * scaleY);

            renderer.Copy(
                textures.getTexture(playerTexture),
                SDL2pp::Rect(1, 10, SPRITE_SIZE, SPRITE_SIZE),
                SDL2pp::Rect(playerSpriteX, y, playerSpriteSizeWidth, playerSpriteSizeHeight)
            );

            int winsX = static_cast<int>(250 * scaleX);
            int winsSizeWidth = static_cast<int>(20 * scaleX);
            int winsSizeHeight = static_cast<int>(20 * scaleY);

            std::string text = std::to_string(static_cast<int>(playerStat.wins));

            SDL2pp::Texture text_sprite(renderer, font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));

		    renderer.Copy(text_sprite, SDL2pp::NullOpt, SDL2pp::Rect(winsX, y + 15, winsSizeWidth, winsSizeHeight));
        }

        y += rowSpacing;
    }
}

void Drawer::drawExplosions() {
    for (const BombExplosion& explosion: animation.getBombExplosions()) {
        int size = explosion.getSpriteSize();
        MapPoint pos = explosion.getPosition();
        renderer.Copy(
                textures.getTexture(explosion.getTexture()),
                SDL2pp::Rect(explosion.getCurrentFrame() * size, 0, size, size),
                SDL2pp::Rect(camera.getScreenX(pos.x) - 50 , camera.getScreenY(-pos.y) - 50,
                             camera.getScaledSize(size),
                             camera.getScaledSize(size)));
    }
}

void Drawer::draw(const MatchDto& matchDto, const MatchStatsInfo& stats) {
    renderer.Clear();

    drawBackground();

    drawObjects(matchDto);

    updateIndicatorFlag();

    drawStatusBar(stats);

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

    drawExplosions();

    // Show rendered frame
    renderer.Present();
}

void Drawer::drawLeaderboard(const MatchStatsInfo& matchStats) {
    int screenWidth = window.GetWidth();
    int screenHeight = window.GetHeight();

    double scaleX = static_cast<double>(screenWidth) / INITIAL_SCREEN_WIDTH;
    double scaleY = static_cast<double>(screenHeight) / INITIAL_SCREEN_HEIGHT;

    renderer.Clear();

    drawBackground();

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

    drawBackground();

    drawObjects(matchDto);

    drawStatusBar(matchStats);

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
