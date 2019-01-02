// Application
// (c) 2018 Jani Nykänen

#ifndef __APP_H__
#define __APP_H__

#include "EventManager.hpp"
#include "Graphics.hpp"


// Application class
class Application {

private:

    // Event manager
    EventManager* evMan;
    // Graphics
    Graphics* graph;

    // Is running
    bool running;

    // Initialize
    void init();
    // Event loop
    void loop();
    // Update
    void update(float delta);
    // Render
    void draw();
    // Dispose
    void dispose();

public:

    // Constructor
    Application();

    // Run
    int run(int argc, char ** argv);

};


#endif // __APP_H__
