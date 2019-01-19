// Title screen scene
// (c) 2019 Jani Nykänen

#ifndef __TITLE_H__
#define __TITLE_H__

#include "../../Core/Scene.hpp"
#include "../../Core/Transition.hpp"

#include "../../Menu.hpp"

// Ending class
class Title : public Scene {

private:

    // Bitmaps
    Bitmap* bmpFont;
    Bitmap* bmpLogo;
    // Samples
    Sample* sAccept;
    Sample* sSelect;

    // Transition
    Transition* trans;
    // Menu
    Menu menu;

    // Logo float timer
    float logoFloat;

public:

    // Terminate
    inline void terminate() {
        evMan->terminate();
    }
    // Go to the stage menu
    void goToStageMenu();

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
        return "title";
    }

};

#endif // __TITLE_H__
