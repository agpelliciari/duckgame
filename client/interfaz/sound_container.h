#ifndef SOUND_CONTAINER_H
#define SOUND_CONTAINER_H

#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

enum class SoundType { JUMP, SHOT };

class SoundContainer {
private:
    SDL2pp::Music backgroundMusic;

    std::unordered_map<SoundType, SDL2pp::Chunk> sounds;  // cppcheck-suppress unusedStructMember

public:
    SoundContainer();

    SDL2pp::Music& getBackgroundMusic();

    SDL2pp::Chunk& getSound(SoundType type);

    ~SoundContainer();
};

#endif
