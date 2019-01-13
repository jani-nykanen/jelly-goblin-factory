// Transition
// (c) 2019 Jani Nykänen

#include "Transition.hpp"

#include <cstdlib>

// Constants
static const float MAX_TIME = 60.0f;


// Constructor
Transition::Transition() {

    timer = 0;
    speed = 0;
    col = Color(0, 0, 0);
    mode = FadeOut;
    active = false;
    cb = NULL;
}


// Update
void Transition::update(float tm) {

    if (!active) return;

    // Update timer
    timer -= speed * tm;
    if(timer <= 0.0f) {      

        // If in
        if(mode == FadeIn)
        {
            // Call callback
            if (cb != NULL)
                cb();

            mode = FadeOut;
            timer = MAX_TIME;
        }
        // If out
        else  {
            
            active = false;
        }
    }
}


// Draw
void Transition::draw(Graphics* g) {

    if(!active) return;

    // Compute fade value
    float t = 1.0f / MAX_TIME * timer;
    if(mode == FadeIn) {

        t = 1.0f - t;
    }

    // Fill
    g->setColor(col.r, col.g, col.b, t);

    // Fill screen
    Vector2 view = g->getViewport();
    g->identity();
    g->useTransf();
    g->fillRect(0, 0, view.x, view.y);

    g->setColor();
}


// Activate
void Transition::activate(int mode, float speed, 
    TransitionCallback cb, Color col) {

    this->mode = mode;
    this->speed = speed;
    this->col = col;
    this->cb = cb;

    timer = MAX_TIME;
    active = true;
}
void Transition::activate(int mode, float speed, TransitionCallback cb) {

    activate(mode, speed, cb, col);
}
