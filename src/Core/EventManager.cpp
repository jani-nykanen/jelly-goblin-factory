// Event manager
// (c) 2019 Jani Nykänen

#include "EventManager.hpp"

#include "Application.hpp"


// Constructor
EventManager::EventManager(Application* ref, void* window, GamePad* vpad) 
    : InputListener(window) {

    appRef = ref;
    this->vpad = vpad;
    trans = Transition();

    // Create audio manager
    // (temporarily here)
    audio = new AudioManager();
}


// Destructor
EventManager::~EventManager() {

    delete audio;
}


// Redirect to application core
void EventManager::terminate() {appRef->terminate();}
void EventManager::toggleFullscreen() {appRef->toggleFullscreen();}
