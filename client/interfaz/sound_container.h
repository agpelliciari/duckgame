#ifndef SOUND_CONTAINER_H
#define SOUND_CONTAINER_H

#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/gameevents.h"


enum class SoundType {
    JUMP,
    SHOT,
    QUACK,
    PEW_PEW_LASER,
    PICK_UP,
    ROUND_END,
    LASER_RIFLE,
    MAGNUM,
    SHOTGUN,
    PISTOL,
    SNIPER,
    BOX_EXPLOSION,
    GRENADE_EXPLOSION,
    GUN_RELOAD,
    POWER_UP,
    BROKEN_ARMOR,
    NONE
};

class SoundContainer {
private:
    SDL2pp::Music backgroundMusic;

    std::unordered_map<SoundType, SDL2pp::Chunk> sounds;  // cppcheck-suppress unusedStructMember

    std::vector<SoundType> MatchSounds;

public:
    SoundContainer();

    SDL2pp::Music& getBackgroundMusic();

    SDL2pp::Chunk& getSound(SoundType type);

    void addSound(SoundEventType soundType);

    void addSound(GameEventType gameSoundType);

    std::vector<SoundType>& getMatchSounds();

    void clearMatchSounds();

    ~SoundContainer();
};

#endif
