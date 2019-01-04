// Application
// (c) 2019 Jani Nykänen

#include "Application.hpp"

#include <stdexcept>
#include <cstdio>


// Initialize GLFW & GL content
void Application::initGL() {

    // Initialize GLFW
    if(glfwInit() == 0) {

        throw std::runtime_error("Failed to initialize GLFW!");
    }

    int width = conf.getIntParam("window_width", 640);
    int height = conf.getIntParam("window_height", 480);
    const char* caption = conf.getParam("caption").c_str();
    
    // Create window
    window = glfwCreateWindow(width, height, caption, NULL, NULL);
    // Set OpenGL context to this window
    glfwMakeContextCurrent(window);

    // Enable VSync
    glfwSwapInterval(1);

    // Initialize GLEW
    if(glewInit() != GLEW_OK) {

        throw std::runtime_error("Failed to initialize GLEW!");
    }
}


// Initialize
void Application::init() {
    
    // Initialize OpenGL content
    initGL();

    // Create event manager
    evMan = new EventManager(this, (void*)window);

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
    
    const int MAX_UPDATE_COUNT = 5;
    const float COMPARED_FPS = 60.0f;

    float timeSum = 0.0f;
    float oldTime = 0.0f;
    glfwSetTime(0.0);

    // Compute desired frame wait
    int steps = conf.getIntParam("refresh_steps", 1);
    float frameWait = 1.0f / (COMPARED_FPS / steps);
    int updateCount = 0;
    bool redraw = false;

    while(running) {

        // Check time
        timeSum += (float)glfwGetTime();
        glfwSetTime(0.0);
        updateCount = 0;
        while(timeSum >= frameWait) {

            // Update frame
            update(steps);
            redraw = true;

            // Make sure we won't be updating the frame
            // too many times
            if(++ updateCount >= MAX_UPDATE_COUNT) {

                timeSum = 0;
                break;
            }

            // Reduce time sum
            timeSum -= frameWait; 
        }

        if(redraw) {

            // Draw
            draw();
            redraw = false;
        }

        // TODO: Draw canvas
        glfwSwapBuffers(window);

        // Window closed
        if(glfwWindowShouldClose(window)) {

            terminate();
        }

        // Poll events
        glfwPollEvents();
    }
}


// Update
void Application::update(int steps) {
    
    // Update scenes
    sceneMan->update(steps);

    // Update input
    evMan->updateInput();
}


// Render
void Application::draw() {

    // Draw scenes
    sceneMan->draw(graph);
}


// Dispose
void Application::dispose() {

    // Dispose scenes
    sceneMan->dispose();

    // Dispose elements
    delete evMan;
    delete sceneMan;

    // Destroy window
    glfwDestroyWindow(window);
}


// Constructor
Application::Application(std::string cfgPath, std::vector<SceneInfo>* scenes) {

    // Parse configuration
    try {

        conf = ConfigData(cfgPath);
    }
    catch(std::runtime_error err) {

        printf("Warning: %s\n", err.what());
    }

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


// Terminate
void Application::terminate() {

    running = false;
}
