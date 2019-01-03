// Application
// (c) 2019 Jani Nykänen

#ifndef __APP_H__
#define __APP_H__

#include <vector>
#include <cstdio>

#include "EventManager.hpp"
#include "Graphics.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"


// Application class
class Application {

private:

    // Event manager
    EventManager* evMan;
    // Scene manager
    SceneManager* sceneMan;
    // Graphics
    Graphics* graph;

    // Scene info storage
    std::vector<SceneInfo>* scenes;

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
    Application(std::vector<SceneInfo>* scenes =NULL);

    // Run
    int run(int argc, char ** argv);

};


#endif // __APP_H__
