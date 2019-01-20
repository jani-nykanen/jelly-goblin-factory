// Audio manager
// (c) 2019 Jani Nykänen

#ifndef __AUDIO_MAN_H__
#define __AUDIO_MAN_H__

#include "Sample.hpp"
#include "Music.hpp"

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

    // Current track
    Music* currentTrack;
    // Current volume
    float currentVol;

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
    void toggleMusic(bool state);
    void toggleMusic();
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
    // Play music
    void playMusic(Music* m, float vol, bool loop=true);
    // Fade in music
    void fadeInMusic(Music* m, float vol, int time=1000, bool loop=true);
    // Fade out music
    void fadeOutMusic(int time=1000);
    // Stop music
    void stopMusic();


};

#endif // __AUDIO_MAN_H__
