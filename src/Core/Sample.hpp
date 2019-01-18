// Sample
// (c) 2019 Jani Nykänen

#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>

// Sample class
class Sample {

private:

    // Info needed for playing the sample
    Mix_Chunk* chunk;
    int channel;
    // Has the sample been played once
    bool played;
    // Successfully loaded
    bool loaded;

public:

    // Constructors
    inline Sample() {};
    Sample(std::string path);
    // Destructor
    ~Sample();

    // Play
    void play(float vol, int loops=0);
    // Stop sample
    void stop();
};

#endif // __SAMPLE_H__
