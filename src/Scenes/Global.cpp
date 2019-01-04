// Global scene
// (c) 2019 Jani Nykänen

#include "Global.hpp"

#include <GLFW/glfw3.h>


// Initialize scene
void Global::init() {

}


// Update scene
void Global::update(int steps) {

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
}



// Draw scene
void Global::draw(Graphics* g) {

}



// Dispose scene
void Global::dispose() {

}
