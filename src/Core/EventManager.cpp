// Event manager
// (c) 2019 Jani Nykänen

#include "EventManager.hpp"

#include "Application.hpp"


// Constructor
EventManager::EventManager(Application* ref, void* window) 
    : InputListener(window) {

    appRef = ref;
}


// Redirect to application core
void EventManager::terminate() {appRef->terminate();}
void EventManager::toggleFullscreen() {appRef->toggleFullscreen();}
