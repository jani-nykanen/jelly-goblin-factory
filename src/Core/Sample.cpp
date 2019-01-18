// Sample
// (c) 2019 Jani Nykänen

#include "Sample.hpp"

#include "Types.hpp"
#include "MathExt.hpp"

#include <cstdio>


// Constructor
Sample::Sample(std::string path) {

    // Load chunk
    chunk = Mix_LoadWAV(path.c_str());
    if(chunk == NULL) {

        printf("Failed to load a WAV file in %s. Ignoring.\n", path.c_str());
        loaded = false;
    }
    loaded = true;
}


// Destructor
Sample::~Sample() {

    // TODO: Destroy chunk?
}


// Play
void Sample::play(float vol, int loops) {

    // Restrict to integers in [0,128]
    int v =  max_int32(0, 
        min_int32(
            (int)(vol*MIX_MAX_VOLUME), 
            MIX_MAX_VOLUME)
        );

    if(!played) {

        // Get channel
        channel = Mix_PlayChannel(-1, chunk, 0);
        Mix_HaltChannel(channel);

        // Play sound
        Mix_Volume(channel, v);
        Mix_PlayChannel(channel, chunk, loops);

        played = true;
    }
    else {

        // Stop & play again
        Mix_HaltChannel(channel);
        Mix_Volume(channel, v);
        Mix_PlayChannel(channel, chunk, loops);
    }
}


// Stop sample
void Sample::stop() {

    Mix_HaltChannel(channel);
}   
