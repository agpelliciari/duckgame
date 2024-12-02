#ifndef ARMOR_DRAWER_H
#define ARMOR_DRAWER_H

#include "equipment_drawer.h"

#define ARMOR_SPRITE_SIZE 32

class ArmorDrawer : public EquipmentDrawer {
private:
    void getParameters(const PlayerDTO& player, SDL_RendererFlip flip, int& chestArmorX, int& chestArmorY, int& helmetArmorX, int& helmetArmorY, float& angle);

public:
    ArmorDrawer(SDL2pp::Renderer& renderer, TextureContainer& textures, Camera& camera);

    void draw(const PlayerDTO& player, SDL_RendererFlip flip) override;

    void drawInfo(const PlayerDTO& player) override;

    ~ArmorDrawer();
};

#endif
