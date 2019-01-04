// Event manager
// (c) 2019 Jani Nykänen

#include "EventManager.hpp"

#include "Application.hpp"


// Constructor
EventManager::EventManager(Application* ref, void* window) 
    : InputListener(window) {

    appRef = ref;
}


// Terminate
void EventManager::terminate() {

    appRef->terminate();
}
