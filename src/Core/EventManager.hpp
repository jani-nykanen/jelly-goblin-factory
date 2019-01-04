// Event manager
// (c) 2019 Jani Nykänen

#ifndef __EVMAN_H__
#define __EVMAN_H__

#include "InputListener.hpp"

class Application;

// Event manager class
class EventManager : public InputListener {

private:

    // Reference to application
    Application* appRef;

public:

    // Constructor
    EventManager(Application* ref, void* window);

    // Redirect to application core
    void terminate();
    void toggleFullscreen();

};

#endif // __EVMAN_H__
