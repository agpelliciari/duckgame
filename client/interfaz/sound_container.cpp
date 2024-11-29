#include "sound_container.h"

SoundContainer::SoundContainer(): backgroundMusic(DATA_PATH "/music/DuckGame-challenging.wav") {
    sounds.emplace(SoundType::JUMP, SDL2pp::Chunk(DATA_PATH "/sounds/jump.mp3"));
    sounds.emplace(SoundType::SHOT, SDL2pp::Chunk(DATA_PATH "/sounds/cowboyPistol.wav"));
    sounds.emplace(SoundType::QUACK, SDL2pp::Chunk(DATA_PATH "/sounds/quack.wav"));
    sounds.emplace(SoundType::LASER, SDL2pp::Chunk(DATA_PATH "/sounds/pewpewLaser.mp3"));
    sounds.emplace(SoundType::PICK_UP, SDL2pp::Chunk(DATA_PATH "/sounds/equip.wav"));
    sounds.emplace(SoundType::ROUND_END, SDL2pp::Chunk(DATA_PATH "/sounds/challengeWin.wav"));
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
        case DUEL_PISTOL_SHOT:
            MatchSounds.push_back(SoundType::SHOT);
            break;
        case PLAYER_PICKUP:
            MatchSounds.push_back(SoundType::PICK_UP);
            break;
        case PLAYER_DIED:
        case PLAYER_FLAP:
        case PLAYER_DROP:
        default:
            break;
    } 
}

std::vector<SoundType>& SoundContainer::getMatchSounds() { return MatchSounds; }

void SoundContainer::clearMatchSounds() { MatchSounds.clear(); }

SoundContainer::~SoundContainer() = default;
