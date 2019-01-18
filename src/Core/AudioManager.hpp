// Audio manager
// (c) 2019 Jani Nykänen

#ifndef __AUDIO_MAN_H__
#define __AUDIO_MAN_H__

#include "Sample.hpp"

// A audio manager class
class AudioManager {

private:

    // States
    bool sfxEnabled;
    bool musicEnabled;
    // If successfully initialized
    // (1 = sfx only)
    // (2 = music & sfx)
    int initialized;

    // Global volumes
    float sfxVolume;
    float musicVolume;

public:

    // Constructor
    AudioManager();

    // Toggle states
    inline void toggleSfx(bool state) {
        sfxEnabled = state;
    }
    inline void toggleSfx() {
        sfxEnabled = !sfxEnabled;
    }
    inline void toggleMusic(bool state) {
        musicEnabled = state;
    }
    inline void toggleMusic() {
        musicEnabled = !musicEnabled;
    }
    inline void setSfxVolume(float vol) {
        sfxVolume = vol;
    }
    inline void setMusicVolume(float vol) {
        musicVolume = vol;
    }

    // Getters
    inline bool isSfxEnabled() {
        return sfxEnabled;
    }
    inline bool isMusicEnabled() {
        return musicEnabled;
    }

    // Play a sample
    void playSample(Sample* s, float vol, int loops=0);


};

#endif // __AUDIO_MAN_H__
