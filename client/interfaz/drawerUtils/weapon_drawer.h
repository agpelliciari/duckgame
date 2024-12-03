#ifndef WEAPON_DRAWER_H
#define WEAPON_DRAWER_H

#include <algorithm>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../animation.h"
#include "equipment_drawer.h"
#include "weapon_builder.h"

#define FLIP 0
#define UNFLIP 1

class WeaponDrawer : public EquipmentDrawer {
private:
    SDL2pp::Font& font; 

    Animation& animation;

    std::unordered_map<TypeWeapon, WeaponBuilder> weaponMap;

    std::unordered_map<TypeWeapon, ExplosionBuilder> explosionMap;

    void getParameters(const PlayerDTO& player, SDL_RendererFlip flip, int& x, int& y, double& angle, int& sizeAdjustment);

    void getShotExplosionParameters(const PlayerDTO& player, SDL_RendererFlip flip, int x, int y, int& explosionX, int& explosionY);

public:
    WeaponDrawer(SDL2pp::Font& font, SDL2pp::Renderer& renderer, TextureContainer& textures, Animation& animation, Camera& camera);

    void draw(const PlayerDTO& player, SDL_RendererFlip flip) override;

    void drawInfo(const PlayerDTO& player) override;

    ~WeaponDrawer();
};

#endif
