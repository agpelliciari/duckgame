#include "weapon_drawer.h"

WeaponDrawer::WeaponDrawer(SDL2pp::Font& font, SDL2pp::Renderer& renderer, TextureContainer& textures, Animation& animation, Camera& camera):
        EquipmentDrawer(renderer, textures, camera), font(font), animation(animation) {
            
            weaponMap = {{TypeWeapon::PISTOLA_COWBOY, WeaponBuilder("/weapons/cowboyPistol.png", COWBOY_GUN_WIDTH, COWBOY_GUN_HEIGHT, {13, -12}, {6, 6}, {-4, 2}, {6, 2}, {60, 7}, 4)},
                         {TypeWeapon::PEW_PEW_LASER, WeaponBuilder("/weapons/pewpewLaser.png", PEW_PEW_LASER_SIZE, PEW_PEW_LASER_SIZE, {20, -15}, {-4, 10}, {-11, -6}, {1, -6}, {54, -3}, 6)},
                         {TypeWeapon::MAGNUM, WeaponBuilder("/weapons/magnum.png", MAGNUM_SIZE, MAGNUM_SIZE, {20, -15}, {-4, 10}, {-11, -6}, {1, -6}, {54, -3}, 6)},
                         {TypeWeapon::PISTOLA_DE_DUELOS, WeaponBuilder("/weapons/pistol.png", PISTOL_SIZE, PISTOL_SIZE, {13, -12}, {6, 6}, {-4, 2}, {6, 2}, {60, 6}, 7)},
                         {TypeWeapon::ESCOPETA, WeaponBuilder("/weapons/shotgun.png", SHOTGUN_SIZE, SHOTGUN_SIZE, {20, -15}, {-4, 10}, {-11, -6}, {1, -6}, {54, -3}, 6)},
                         {TypeWeapon::SNIPER, WeaponBuilder("/weapons/sniper.png", SNIPER_WIDTH, SNIPER_HEIGHT, {12, -24}, {6, 6}, {-18, 2}, {0, 2}, {60, 8}, 0)},
                         {TypeWeapon::AK_47, WeaponBuilder("/weapons/ak47.png", AK47_SIZE, AK47_SIZE, {20, -15}, {-4, 10}, {-11, -6}, {1, -6}, {54, -3}, 6)},
                         {TypeWeapon::LASER_RIFLE, WeaponBuilder("/weapons/laserRifle.png", LASER_RIFLE_SIZE, LASER_RIFLE_SIZE, {20, -15}, {-4, 10}, {-11, -6}, {1, -6}, {54, -3}, 6)},
                         {TypeWeapon::GRANADA, WeaponBuilder("/weapons/grenade.png", GRENADE_SIZE, GRENADE_SIZE, {13, -12}, {6, 6}, {-4, 2}, {6, 2}, {55, 7}, 4)},
                         {TypeWeapon::BANANA, WeaponBuilder("/weapons/banana.png", BANANA_SIZE, BANANA_SIZE, {15, -8}, {-2, 5}, {-4, -3}, {6, -2}, {55, 1}, 2)}};
            
            explosionMap = {{TypeWeapon::PISTOLA_COWBOY, ExplosionBuilder({8, -20}, {-8, -30}, {-20, -8}, {30, -8})},
                            {TypeWeapon::PEW_PEW_LASER, ExplosionBuilder({-6, -25}, {6, -45}, {-15, 8}, {50, 8})},
                            {TypeWeapon::ESCOPETA, ExplosionBuilder({-12, -25}, {14, -57}, {-25, 12}, {56, 12})},
                            {TypeWeapon::SNIPER, ExplosionBuilder({3, -25}, {-4, -68}, {-27, -4}, {65, -4})},
                            {TypeWeapon::LASER_RIFLE, ExplosionBuilder({10, -60}, {-8, -45}, {-55, -10}, {45, -10})},
                            {TypeWeapon::PISTOLA_DE_DUELOS, ExplosionBuilder({-8, -15}, {8, -42}, {-12, 8}, {43, 8})},
                            {TypeWeapon::MAGNUM, ExplosionBuilder({-8, -15}, {8, -42}, {-12, 8}, {43, 8})},
                            {TypeWeapon::AK_47, ExplosionBuilder({-12, -25}, {14, -57}, {-25, 12}, {56, 12})},
                            {TypeWeapon::GRANADA, ExplosionBuilder({-8, -15}, {8, -42}, {-12, 8}, {43, 8})},
                            {TypeWeapon::BANANA, ExplosionBuilder({-8, -15}, {8, -42}, {-12, 8}, {43, 8})}};
}

void WeaponDrawer::getParameters(const PlayerDTO& player, SDL_RendererFlip flip, int& x, int& y, double& angle, int& sizeAdjustment) {
    auto weapon = weaponMap.find(player.weapon);
    if (weapon != weaponMap.end()) {
        const auto& [texture, width, height, aimUpParameters, normalParameters, hudParameters, adjustment] = weapon->second;

        if (player.aiming_up) {
            angle = getTextureFlipValue(flip, 90.0, -90.0);
            x = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, std::get<FLIP>(aimUpParameters).first, std::get<UNFLIP>(aimUpParameters).first));
            y = camera.getScreenY(player.pos.y + getTextureFlipValue(flip, std::get<FLIP>(aimUpParameters).second, std::get<UNFLIP>(aimUpParameters).second));
        } else {
            angle = 0.0;
            x = camera.getScreenX(player.pos.x + getTextureFlipValue(flip, std::get<FLIP>(normalParameters).first, std::get<UNFLIP>(normalParameters).first));
            y = camera.getScreenY(player.pos.y + getTextureFlipValue(flip, std::get<FLIP>(normalParameters).second, std::get<UNFLIP>(normalParameters).second));
        }

        sizeAdjustment = adjustment;
    }
    
}

void WeaponDrawer::getShotExplosionParameters(const PlayerDTO& player, SDL_RendererFlip flip, int x, int y, int& explosionX, int& explosionY) {
    auto explosion = explosionMap.find(player.weapon);
    if (explosion != explosionMap.end()) {
        const auto& [aimUpParameters, normalParameters] = explosion->second;

        if (player.aiming_up) {
            explosionX = x + getTextureFlipValue(flip, std::get<FLIP>(aimUpParameters).first, std::get<UNFLIP>(aimUpParameters).first);
            explosionY = y + getTextureFlipValue(flip, std::get<FLIP>(aimUpParameters).second, std::get<UNFLIP>(aimUpParameters).second);
        } else {
            explosionX = x + getTextureFlipValue(flip, std::get<FLIP>(normalParameters).first, std::get<UNFLIP>(normalParameters).first);
            explosionY = y + getTextureFlipValue(flip, std::get<FLIP>(normalParameters).second, std::get<UNFLIP>(normalParameters).second);
        }
    }
}

void WeaponDrawer::draw(const PlayerDTO& player, SDL_RendererFlip flip) {
    auto weapon = weaponMap.find(player.weapon);
    if (weapon != weaponMap.end()) {
        const auto& [textureType, width, height, aimUpParameters, normalParameters, hudParameters, adjustment] = weapon->second;

        int x, y, sizeAdjustment;
        double angle;

        getParameters(player, flip, x, y, angle, sizeAdjustment);

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

void WeaponDrawer::drawInfo(const PlayerDTO& player) {
    auto weapon = weaponMap.find(player.weapon);
    if (weapon != weaponMap.end()) {
        const auto& [textureType, width, height, aimUpParameters, normalParameters, hudParameters, adjustment] = weapon->second;

        int x = hudParameters.first;
        int y = hudParameters.second;

        renderer.Copy(textures.getTexture(textureType), SDL2pp::Rect(0, 0, width, height),
                      SDL2pp::Rect(x + 115 * (player.id - 1), y, width, height));
        
        std::string text = std::to_string(player.munition);
        SDL2pp::Texture text_sprite(renderer, font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));

        renderer.Copy(text_sprite, SDL2pp::NullOpt,
                      SDL2pp::Rect(x + 45 + 115 * (player.id - 1), 9, 12, 12));
    }
}

WeaponDrawer::~WeaponDrawer() = default;
