// Application
// (c) 2018 Jani Nykänen

#include "Application.hpp"

#include <stdexcept>
#include <cstdio>


// Initialize
void Application::init() {
    
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

}


// Constructor
Application::Application() {

    // ...
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
