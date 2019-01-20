// Intro screen scene
// (c) 2019 Jani Nykänen

#ifndef __INTRO_H__
#define __INTRO_H__

#include "../../Core/Scene.hpp"
#include "../../Core/Transition.hpp"

// Intro class
class Intro : public Scene {

private:

    // Bitmaps
    Bitmap* bmpCreator;

    // Transition
    Transition* trans;
    // Cog angle
    float cogAngle;

    // Timer
    float timer;

public:

    // Go to the title screen
    void goToTitle();

    // Initialize scene
    void init();
    // Update scene
    void update(float tm);
    // Draw scene
    void draw(Graphics* g);
    // Destroy scene
    void dispose();
    // On change
    void onChange(void* param=NULL);

    // Get name
    inline std::string getName() {
        return "intro";
    }

};

#endif // __INTRO_H__
