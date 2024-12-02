#include "armor_drawer.h"

ArmorDrawer::ArmorDrawer(SDL2pp::Renderer& renderer, TextureContainer& textures, Camera& camera):
        EquipmentDrawer(renderer, textures, camera) {}

void ArmorDrawer::getParameters(const PlayerDTO& player, SDL_RendererFlip flip, int& chestArmorX, int& chestArmorY, int& helmetArmorX, int& helmetArmorY, float& angle) {
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

void ArmorDrawer::draw(const PlayerDTO& player, SDL_RendererFlip flip) {
    int chestArmorX, chestArmorY, helmetArmorX, helmetArmorY;
    float angle = 0.0;
    
    getParameters(player, flip, chestArmorX, chestArmorY, helmetArmorX, helmetArmorY, angle);

    if (player.helmet) {
        renderer.Copy(
                textures.getTexture("/armors/helmet.png"),
                SDL2pp::Rect(0, 0, ARMOR_SPRITE_SIZE, ARMOR_SPRITE_SIZE),
                SDL2pp::Rect(helmetArmorX, helmetArmorY,
                        camera.getScaledSize(ARMOR_SPRITE_SIZE - 3), camera.getScaledSize(ARMOR_SPRITE_SIZE - 3)),
                angle, SDL2pp::Point(0, 0), flip);
    }


    if (player.chest_armor) {
        renderer.Copy(
                textures.getTexture("/armors/chestPlateAnim.png"),
                SDL2pp::Rect(0, 0, ARMOR_SPRITE_SIZE, ARMOR_SPRITE_SIZE),
                SDL2pp::Rect(chestArmorX, chestArmorY,
                             camera.getScaledSize(ARMOR_SPRITE_SIZE - 3), camera.getScaledSize(ARMOR_SPRITE_SIZE - 3)),
                angle, SDL2pp::Point(0, 0), flip);
    }
}

void ArmorDrawer::drawInfo(const PlayerDTO& player) {
    if (player.helmet) {
        renderer.Copy(textures.getTexture("/armors/helmet.png"), SDL2pp::Rect(0, 0, ARMOR_SPRITE_SIZE, ARMOR_SPRITE_SIZE),
                      SDL2pp::Rect(8 + 115 * (player.id - 1), -9, ARMOR_SPRITE_SIZE, ARMOR_SPRITE_SIZE));
    }

    if (player.chest_armor) {
        renderer.Copy(textures.getTexture("/armors/chestPlateAnim.png"),
                      SDL2pp::Rect(0, 0, ARMOR_SPRITE_SIZE, 16),
                      SDL2pp::Rect(10 + 115 * (player.id - 1), -6, ARMOR_SPRITE_SIZE, ARMOR_SPRITE_SIZE));
    }
}

ArmorDrawer::~ArmorDrawer() = default;
