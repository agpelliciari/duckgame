#include "object_drawer.h"

ObjectDrawer::ObjectDrawer(SDL2pp::Renderer& renderer, TextureContainer& textures, Camera& camera, const GameContext& context) :
        renderer(renderer), textures(textures), camera(camera), context(context) {}

void ObjectDrawer::draw(const MapObject& object) {
    renderer.Copy(
            textures.getTexture(object.texture), SDL2pp::Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT),
            SDL2pp::Rect(camera.getScreenX(object.column * BLOCK_WIDTH),
                         camera.getScreenY(-object.row * BLOCK_HEIGHT),
                         camera.getScaledSize(BLOCK_WIDTH), camera.getScaledSize(BLOCK_HEIGHT)));
}

void ObjectDrawer::draw(const DynamicObjDTO& object) {
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
        
        case TypeDynamicObject::THROWN_BANANA:
            renderer.Copy(
                    textures.getTexture("/weapons/banana.png"), SDL2pp::Rect(0, 16, BANANA_SIZE, BANANA_SIZE),
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

        case TypeDynamicObject::PISTOLA_DE_DUELOS:
            renderer.Copy(textures.getTexture("/weapons/pistol.png"), SDL2pp::Rect(0, 0, PISTOL_SIZE, PISTOL_SIZE), SDL2pp::Rect(camera.getScreenX(object.pos.x) + 5, camera.getScreenY(-object.pos.y) + 10, camera.getScaledSize(PISTOL_SIZE - 6), camera.getScaledSize(PISTOL_SIZE - 6)));
            break;

        case TypeDynamicObject::PISTOLA_COWBOY:
            renderer.Copy(
                    textures.getTexture("/weapons/cowboyPistol.png"),
                    SDL2pp::Rect(0, 0, COWBOY_GUN_WIDTH, COWBOY_GUN_HEIGHT),
                    SDL2pp::Rect(camera.getScreenX(object.pos.x + 3), camera.getScreenY(-object.pos.y + 5),
                                 camera.getScaledSize(COWBOY_GUN_WIDTH - 3),
                                 camera.getScaledSize(COWBOY_GUN_HEIGHT - 3)));
            break;
        
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

ObjectDrawer::~ObjectDrawer() = default;
