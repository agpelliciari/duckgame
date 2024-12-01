#include "sound_container.h"

SoundContainer::SoundContainer(): backgroundMusic(DATA_PATH "/music/DuckGame-challenging.wav") {
    sounds.emplace(SoundType::JUMP, SDL2pp::Chunk(DATA_PATH "/sounds/jump.mp3"));
    sounds.emplace(SoundType::SHOT, SDL2pp::Chunk(DATA_PATH "/sounds/cowboyPistol.wav"));
    sounds.emplace(SoundType::QUACK, SDL2pp::Chunk(DATA_PATH "/sounds/quack.wav"));
    sounds.emplace(SoundType::PEW_PEW_LASER, SDL2pp::Chunk(DATA_PATH "/sounds/pewpewLaser.mp3"));
    sounds.emplace(SoundType::PICK_UP, SDL2pp::Chunk(DATA_PATH "/sounds/equip.wav"));
    sounds.emplace(SoundType::ROUND_END, SDL2pp::Chunk(DATA_PATH "/sounds/challengeWin.wav"));
    sounds.emplace(SoundType::LASER_RIFLE, SDL2pp::Chunk(DATA_PATH "/sounds/laserRifle.wav"));
    sounds.emplace(SoundType::PISTOL, SDL2pp::Chunk(DATA_PATH "/sounds/pistol.wav"));
    sounds.emplace(SoundType::MAGNUM, SDL2pp::Chunk(DATA_PATH "/sounds/magnum.wav"));
    sounds.emplace(SoundType::SHOTGUN, SDL2pp::Chunk(DATA_PATH "/sounds/shotgun.wav"));
    sounds.emplace(SoundType::SNIPER, SDL2pp::Chunk(DATA_PATH "/sounds/sniper.wav"));
    sounds.emplace(SoundType::GRENADE_EXPLOSION, SDL2pp::Chunk(DATA_PATH "/sounds/explode.wav"));
    sounds.emplace(SoundType::BOX_EXPLOSION, SDL2pp::Chunk(DATA_PATH "/sounds/crateDestroy.wav"));
    sounds.emplace(SoundType::GUN_RELOAD, SDL2pp::Chunk(DATA_PATH "/sounds/reload.wav"));
    sounds.emplace(SoundType::POWER_UP, SDL2pp::Chunk(DATA_PATH "/sounds/powerUp.wav"));
    sounds.emplace(SoundType::BROKEN_ARMOR, SDL2pp::Chunk(DATA_PATH "/sounds/brokenArmor.wav"));
    sounds.emplace(SoundType::FLAP, SDL2pp::Chunk(DATA_PATH "/sounds/flap.wav"));
}

SDL2pp::Music& SoundContainer::getBackgroundMusic() { return backgroundMusic; }

SDL2pp::Chunk& SoundContainer::getSound(SoundType type) { return sounds.at(type); }

void SoundContainer::addSound(SoundEventType soundType) { 
    switch (soundType) {
        case PLAYER_JUMPED:
            MatchSounds.push_back(SoundType::JUMP);
            break;
        case PLAYER_DAMAGED:
            MatchSounds.push_back(SoundType::QUACK);
            break;
        case PLAYER_PICKUP:
            MatchSounds.push_back(SoundType::PICK_UP);
            break;
        case PEWPEW_SHOT:
            MatchSounds.push_back(SoundType::PEW_PEW_LASER);
            break;
        case LASER_SHOT:
            MatchSounds.push_back(SoundType::LASER_RIFLE);
            break;
        case SNIPER_SHOT:
            MatchSounds.push_back(SoundType::SNIPER);
            break;
        case AK47_SHOT:    
        case DUEL_PISTOL_SHOT:
            MatchSounds.push_back(SoundType::PISTOL);
            break;
        case COWBOY_SHOT:
            MatchSounds.push_back(SoundType::SHOT);
            break;
        case MAGNUM_SHOT:
            MatchSounds.push_back(SoundType::MAGNUM);
            break;
        case SHOTGUN_SHOT:
            MatchSounds.push_back(SoundType::SHOTGUN);
            break;
        case PLAYER_EQUIP_ARMOR:
        case PLAYER_EQUIP_HELMET:
            MatchSounds.push_back(SoundType::POWER_UP);
            break;
        case PLAYER_BROKEN_ARMOR:
        case PLAYER_BROKEN_HELMET:
            MatchSounds.push_back(SoundType::BROKEN_ARMOR);
            break;
        case PLAYER_RELOADING:
            MatchSounds.push_back(SoundType::GUN_RELOAD);
            break;
        case PLAYER_FLAP:
            MatchSounds.push_back(SoundType::FLAP);
            break;
        default:
            break;
    } 
}

void SoundContainer::addSound(GameEventType gameSoundType) {
    switch (gameSoundType) {
        case BOMB_EXPLOSION:    
        case GRENADE_EXPLOSION:
            MatchSounds.push_back(SoundType::GRENADE_EXPLOSION);
            break;
        case BOX_DESTROYED:
            MatchSounds.push_back(SoundType::BOX_EXPLOSION);
            break;
        case BANANA_EXPLOSION:
        case NO_EVENT:
        default:
            break;
    }
}

std::vector<SoundType>& SoundContainer::getMatchSounds() { return MatchSounds; }

void SoundContainer::clearMatchSounds() { MatchSounds.clear(); }

SoundContainer::~SoundContainer() = default;
