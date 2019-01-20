// Music track
// (c) 2019 Jani Nykänen

#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <SDL2/SDL_mixer.h>

#include <string>


// Music track type
class Music {

private:

    // Music track
    Mix_Music* track;

    // Is successfully loaded
    bool loaded;

public:

    // Constructor
    Music(std::string path);

    // Play
    void play(float vol, bool loop=true);
    // Fade in
    void fadeIn(float vol, int time=1000, bool loop=true);
    // Stop
    void stop();
};


#endif // __MUSIC_H__
