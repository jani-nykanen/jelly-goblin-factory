// Audio manager
// (c) 2019 Jani Nykänen

#include "AudioManager.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <cstdio>


// Constructor
AudioManager::AudioManager() {

    // Set defaults
    sfxEnabled = true;
    musicEnabled = true;
    sfxVolume = 1.0f;
    musicVolume = 1.0f;
    currentTrack = NULL;
    currentVol = 1.0f;

    // Initialize SDL2
    initialized = 0;
    if(SDL_Init(SDL_INIT_AUDIO) == -1) {
        
        printf("Failed to initialize SDL2. Audio disabled.\n");
        return;
    }
    initialized = 2;

    // Open audio
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) == -1) {

        initialized = 0;
        printf("Failed to open audio. Audio disabled.\n");
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        return;
    }

    // Initialize Mixer
    int flags = MIX_INIT_OGG;
    int ret =  Mix_Init(flags);
    if((ret & flags) != flags) {

        initialized = 1;
        printf("Failed to initialize OGG addon. Music possibly disabled.\n");
        printf("SDL_Mixer: %s\n", Mix_GetError());
    }
}


// Toggle music
void AudioManager::toggleMusic(bool state) {

    musicEnabled = state;
    if(!state) {

        Mix_HaltMusic();
    }
    else {

        if(currentTrack != NULL) {

            // Replay music
            playMusic(currentTrack, currentVol);
        }
    }
}
void AudioManager::toggleMusic() {

    toggleMusic(!musicEnabled);
}



// Play a sample
void AudioManager::playSample(Sample* s, float vol, int loops) {

    if(s == NULL || initialized == 0 || !sfxEnabled) 
        return;

    s->play(vol*sfxVolume, loops);
}


// Play music
void AudioManager::playMusic(Music* m, float vol, bool loop) {

    currentTrack = m;
    currentVol = musicVolume * vol;

    if(!musicEnabled) return;

    m->play(currentVol, loop);
}



// Fade in music
void AudioManager::fadeInMusic(Music* m, float vol, int time, bool loop) {

    currentTrack = m;
    currentVol = musicVolume * vol;

    if(!musicEnabled) return;

    m->fadeIn(currentVol, time, loop);
}



// Fade out music
void AudioManager::fadeOutMusic(int time) {

    currentTrack = NULL;
    currentVol = 0.0f;

    if(!musicEnabled) return;

    Mix_FadeOutMusic(time);
}



// Stop music
void AudioManager::stopMusic() {

    currentTrack = NULL;
    currentVol = 0.0f;

    if(!musicEnabled) return;

    Mix_HaltMusic();
}
