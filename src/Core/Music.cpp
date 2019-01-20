// Music track
// (c) 2019 Jani Nykänen

#include "Music.hpp"

#include "MathExt.hpp"


// Constructor
Music::Music(std::string path) {

    loaded = false;

    // Load
    track = Mix_LoadMUS(path.c_str());
    if(track == NULL) {

        printf("Failed to load a music track in %s. Ignoring.\n",
            path.c_str());
        return;
    }
    loaded = true;
}


// Play
void Music::play(float vol, bool loop) {

    if(!loaded) return;

    int v = max_int32(0, 
        min_int32(
            (int)(vol*MIX_MAX_VOLUME), 
            MIX_MAX_VOLUME)
        );

    Mix_VolumeMusic(v);
    Mix_PlayMusic(track, loop ? -1 : 0);
}


// Fade in
void Music::fadeIn(float vol, int time, bool loop) {

    if(!loaded) return;

    int v = max_int32(0, 
        min_int32(
            (int)(vol*MIX_MAX_VOLUME), 
            MIX_MAX_VOLUME)
        );

    Mix_VolumeMusic(v);
    Mix_FadeInMusic(track, loop ? -1 : 0, time);
}
