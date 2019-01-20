// Global scene
// (c) 2019 Jani Nykänen

#include "Global.hpp"

#include "../Menu.hpp"

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <ctime>


// Initialize scene
void Global::init() {

    // Only affects animation
    srand(time(NULL));

    // Update certain global components
    initGlobalMenu(assets);

    // Set transition
    trans = evMan->getTransition();
    trans->activate(FadeOut, 1.0f, NULL, Color(0.0f, 0.0f, 0.0f));
}


// Update scene
void Global::update(float tm) {

    // Default keyboard shortcuts
    // 1) Terminate
    if(evMan->getKeyState(GLFW_KEY_LEFT_CONTROL) == State::Down
    && evMan->getKeyState(GLFW_KEY_Q) == State::Pressed) {

        evMan->terminate();
    }
    // 2) Toggle fullscreen
    if( (evMan->getKeyState(GLFW_KEY_LEFT_ALT) == State::Down
    && evMan->getKeyState(GLFW_KEY_ENTER) == State::Pressed) ||
        evMan->getKeyState(GLFW_KEY_F4) == State::Pressed ){

        evMan->toggleFullscreen();
    }

    // Update transition
    trans->update(tm);
}



// Draw scene
void Global::draw(Graphics* g) {

    // Draw transition
   trans->draw(g);
}



// Dispose scene
void Global::dispose() {

}
