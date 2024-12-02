#ifndef WEAPON_BUILDER_H
#define WEAPON_BUILDER_H

#include <string>
#include <tuple>
#include <utility>

#define COWBOY_GUN_WIDTH 22
#define COWBOY_GUN_HEIGHT 11
#define PEW_PEW_LASER_SIZE 32
#define MAGNUM_SIZE 32
#define PISTOL_SIZE 18
#define GRENADE_SIZE 16
#define BANANA_SIZE 16
#define SHOTGUN_SIZE 32
#define SNIPER_WIDTH 33
#define SNIPER_HEIGHT 9
#define AK47_SIZE 32
#define LASER_RIFLE_SIZE 32

struct WeaponBuilder {
    std::string texture;
    int width;
    int height;
    std::tuple<std::pair<int, int>, std::pair<int, int>> aimUpParameters;
    std::tuple<std::pair<int, int>, std::pair<int, int>> normalParameters;
    std::pair<int, int> hudParameters;
    int sizeAdjustment;

    // params: tex, w, h, {aimup: {flip: {x,y}, unflip: {x,y}}}, {normal: {flip: {x,y}, unflip: {x,y}}}, {hud: {x,y}}, adjustment
    WeaponBuilder(std::string texture, int width, int height, std::pair<int, int> aimUpFlip, std::pair<int, int> aimUpUnflip, std::pair<int, int> normalFlip, std::pair<int, int> normalUnflip, std::pair<int, int> hudParameters, int sizeAdjustment)
        : texture(texture), width(width), height(height), aimUpParameters({aimUpFlip, aimUpUnflip}), normalParameters({normalFlip, normalUnflip}), hudParameters(hudParameters), sizeAdjustment(sizeAdjustment) {}

};

struct ExplosionBuilder {
    std::tuple<std::pair<int, int>, std::pair<int, int>> aimUpParameters;
    std::tuple<std::pair<int, int>, std::pair<int, int>> normalParameters;

    // params: {aimup: {flip: {x,y}, unflip: {x,y}}}, {normal: {flip: {x,y}, unflip: {x,y}}}
    ExplosionBuilder(std::pair<int, int> aimUpFlip, std::pair<int, int> aimUpUnflip, std::pair<int, int> normalFlip, std::pair<int, int> normalUnflip)
        : aimUpParameters({aimUpFlip, aimUpUnflip}), normalParameters({normalFlip, normalUnflip}) {}
};

#endif
