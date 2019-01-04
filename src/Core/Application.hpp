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
#include "Config.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


// Application class
class Application {

private:

    // Window
    GLFWwindow* window;

    // Event manager
    EventManager* evMan;
    // Scene manager
    SceneManager* sceneMan;
    // Graphics
    Graphics* graph;

    // Scene info storage
    std::vector<SceneInfo>* scenes;
    // Configuration
    ConfigData conf;

    // Is running
    bool running;

    // Initialize GLFW & GL content
    void initGL();

    // Initialize
    void init();
    // Event loop
    void loop();
    // Update
    void update(int steps);
    // Render
    void draw();
    // Dispose
    void dispose();

public:

    // Constructor
    Application(std::string cfgPath, std::vector<SceneInfo>* scenes =NULL);

    // Run
    int run(int argc, char ** argv);
    // Terminate
    void terminate();

};


#endif // __APP_H__
