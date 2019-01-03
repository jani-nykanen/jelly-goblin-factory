// Application
// (c) 2019 Jani Nykänen

#include "Application.hpp"

#include <stdexcept>
#include <cstdio>


// Initialize
void Application::init() {
    
    // Create scene manager
    sceneMan = new SceneManager(evMan);
    // Add scenes
    SceneInfo sinfo;
    for(int i = 0; i < scenes->size(); ++ i) {
        
        sinfo = (*scenes)[i];
        sceneMan->addScene(sinfo.s, sinfo.makeActive, sinfo.makeGlobal);
    }

    // Initialize scenes
    sceneMan->init();

    // Set running
    running = true;
}


// Event loop
void Application::loop() {
    
    while(running) {

        // Update
        update(0.0f);
        // Draw
        draw();

        running = false;
    }
}


// Update
void Application::update(float delta) {
    
}


// Render
void Application::draw() {

}


// Dispose
void Application::dispose() {

    // Dispose scenes
    sceneMan->dispose();
}


// Constructor
Application::Application(std::vector<SceneInfo>* scenes) {

    // Store scenes for future use
    this->scenes = scenes;
}


// Run
int Application::run(int argc, char ** argv) {

    try {

        // Initialize
        init();
        // Loop
        loop();

        // Dispose data
        dispose();
    }
    catch(std::runtime_error err) {

        printf("Error: %s\n", err.what());
        return 1;
    }

    return 0;
}
