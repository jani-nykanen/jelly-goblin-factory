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

    // Initialize SDL2
    initialized = 0;
    if(SDL_Init(SDL_INIT_AUDIO) == -1) {
        
        printf("Failed to initialize SDL2. Audio disabled.\n");
        return;
    }
    initialized = 2;

    // Initialize Mixer
    int flags=0; // MIX_INIT_OGG;
   //int ret = 
     Mix_Init(flags);
    /*if((ret & flags) != flags) {

        initialized = 1;
        printf("Failed to initialize OGG addon. Music disabled.\n");
    }*/

    // Open audio
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) == -1) {

        initialized = 0;
        printf("Failed to open audio. Audio disabled.\n");
        return;
    }
}


// Play a sample
void AudioManager::playSample(Sample* s, float vol, int loops) {

    if(s == NULL || initialized == 0 || !sfxEnabled) 
        return;

    s->play(vol*sfxVolume, loops);
}
