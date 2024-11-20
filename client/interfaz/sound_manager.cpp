#include "sound_manager.h"

SoundManager::SoundManager():
        mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, MIX_DEFAULT_CHUNKSIZE), sounds() {}

void SoundManager::playBackgroundMusic() {
    mixer.SetMusicVolume(10);
    mixer.FadeInMusic(sounds.getBackgroundMusic(), -1, 1000);
}

void SoundManager::stopBackgroundMusic() { mixer.HaltMusic(); }

void SoundManager::playSound(SoundType sound) { mixer.PlayChannel(1, sounds.getSound(sound), 0); }

SoundManager::~SoundManager() = default;
