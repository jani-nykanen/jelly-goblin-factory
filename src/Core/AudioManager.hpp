// Audio manager
// (c) 2019 Jani Nykänen

#ifndef __AUDIO_MAN_H__
#define __AUDIO_MAN_H__

// A dummy audio manager class
class AudioManager {

private:

    // States
    bool sfxEnabled;
    bool musicEnabled;

public:

    // Constructor
    inline AudioManager() {
        sfxEnabled = true;
        musicEnabled = true;
    }

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

    // Getters
    inline bool isSfxEnabled() {
        return sfxEnabled;
    }
    inline bool isMusicEnabled() {
        return musicEnabled;
    }


};

#endif // __AUDIO_MAN_H__
