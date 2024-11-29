#include "sound_manager.h"

SoundManager::SoundManager():
        mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, MIX_DEFAULT_CHUNKSIZE), sounds(), roundEndSoundAvailable(true) {}

void SoundManager::playBackgroundMusic() {
    mixer.SetMusicVolume(10);
    mixer.FadeInMusic(sounds.getBackgroundMusic(), -1, 1000);
}

void SoundManager::stopBackgroundMusic() { mixer.HaltMusic(); }

void SoundManager::addMatchSound(SoundEventType soundType) { sounds.addSound(soundType); }

void SoundManager::playSounds() {
    int soundsPlayed = 0;
    for (SoundType sound: sounds.getMatchSounds()) {
        if (soundsPlayed > MAX_SOUNDS_PER_FRAME) {
            break;
        }
        playSound(sound);
        soundsPlayed++;
    }

    sounds.clearMatchSounds();
}

void SoundManager::playSound(SoundType sound) { mixer.PlayChannel(1, sounds.getSound(sound), 0); }

bool SoundManager::isRoundEndSoundAvailable() const { return roundEndSoundAvailable; }

void SoundManager::setRoundEndSoundAvailability(bool availability) { roundEndSoundAvailable = availability; }

SoundManager::~SoundManager() = default;
