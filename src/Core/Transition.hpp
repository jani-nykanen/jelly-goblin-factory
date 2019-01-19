// Transition
// (c) 2019 Jani Nykänen

#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include "Graphics.hpp"

// Fade modes
enum {
    FadeIn = 0,
    FadeOut = 1
};

// Callback type
typedef void (*TransitionCallback) (void);

// Transition class
class Transition {

private:

    // Fading mode
    int mode;
    // Is active
    bool active;
    // Timer
    float timer;
    // Color
    Color col;
    // Speed
    float speed;
    // Callback
    TransitionCallback cb;

public:

    // Constructor
    Transition();

    // Update
    void update(float tm);
    // Draw
    void draw(Graphics* g);

    // Activate
    void activate(int mode, float speed, TransitionCallback cb, Color col);
    void activate(int mode, float speed, TransitionCallback cb = NULL);

    // Is active
    inline bool isActive() {
        return active;
    }
    // Get time in [0,1)
    float getTime();
};

#endif // __TRANSITION_H__
