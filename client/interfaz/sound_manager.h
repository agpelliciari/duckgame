#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "sound_container.h"

#define MIX_DEFAULT_CHUNKSIZE 2048
#define MAX_SOUNDS_PER_FRAME 3

class SoundManager {
private:
    SDL2pp::Mixer mixer;

    SoundContainer sounds;

    bool roundEndSoundAvailable;

public:
    SoundManager();

    void playBackgroundMusic();

    void stopBackgroundMusic();

    void addMatchSound(SoundEventType soundType);

    void playSounds();

    void playSound(SoundType sound);

    bool isRoundEndSoundAvailable() const;

    void setRoundEndSoundAvailability(bool availability);

    ~SoundManager();
};

#endif
