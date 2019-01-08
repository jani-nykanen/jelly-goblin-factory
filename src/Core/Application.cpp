// Application
// (c) 2019 Jani Nykänen

#include "Application.hpp"

#include <stdexcept>
#include <cstdio>

#include <GL/gl.h>


// Reference to self
static Application* self;


// Resize event
static void resizeFramebuffer(GLFWwindow* window, 
    int width, int height) {

    self->resize(width, height);
}


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
    winSize[0] = width;
    winSize[1] = height;
    // Set OpenGL context to this window
    glfwMakeContextCurrent(window);

    // Toggle fullscreen, if wanted
    bool fs = conf.getIntParam("fullscreen", 0) == 1;
    fullscreen = false;
    if(fs) {

        toggleFullscreen();
    }
    else {

        fullscreen = false;
    }

    // Enable VSync
    glfwSwapInterval(1);

    // Initialize GLEW
    if(glewInit() != GLEW_OK) {

        throw std::runtime_error("Failed to initialize GLEW!");
    }

    // Hide cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Register core events
    self = this;
    glfwSetFramebufferSizeCallback(window, resizeFramebuffer);
}


// Initialize
void Application::init() {
    
    // Initialize OpenGL content
    initGL();

    // Create graphics
    graph = new Graphics();
    graph->resize(winSize[0], winSize[1]);

    // Create event manager
    evMan = new EventManager(this, (void*)window);

    // Create scene manager
    sceneMan = new SceneManager(evMan);
    // Add scenes
    SceneInfo sinfo;
    for(int i = 0; i < scenes.size(); ++ i) {
        
        sinfo = scenes[i];
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
    float framerate = conf.getIntParam("framerate", 60);
    float tm = COMPARED_FPS / framerate;
    float frameWait = 1.0f / framerate;

    int updateCount = 0;
    bool redraw = false;

    while(running) {

        // Check time
        timeSum += (float)glfwGetTime();
        glfwSetTime(0.0);
        updateCount = 0;
        while(timeSum >= frameWait) {

            // Update frame
            update(tm);
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

        // Draw
        draw();
        // Swap buffers
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

    // Reset graphics matrix stack
    graph->resetStack();
}


// Dispose
void Application::dispose() {

    // Dispose scenes
    sceneMan->dispose();

    // Dispose elements
    delete evMan;
    delete sceneMan;
    delete graph;

    // Destroy window
    glfwDestroyWindow(window);
}


// Constructor
Application::Application(std::string cfgPath, std::vector<SceneInfo> scenes) {

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


// Toggle fullscreen
void Application::toggleFullscreen() {

    fullscreen = !fullscreen;
    if(fullscreen) {

        // Store old window information
        glfwGetWindowPos(window, &prevWinPos[0], &prevWinPos[1]);
        glfwGetWindowSize(window, &prevWinSize[0], &prevWinSize[1]);

        // Get monitor pointer & video mode
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* video = glfwGetVideoMode(monitor);

		// Enable full screen mode
		glfwSetWindowMonitor(window, monitor, 0, 0, 
            video->width, video->height, GLFW_DONT_CARE );
    }
    else {

        // Reset window
		glfwSetWindowMonitor(window, NULL,
				prevWinPos[0], prevWinPos[1],
				prevWinSize[0], prevWinSize[1],
				GLFW_DONT_CARE);

		// Store current window size
		winSize[0] = prevWinSize[0];
		winSize[1] = prevWinSize[1];
    }
}


// Resize event
void Application::resize(int width, int height) {

    winSize[0] = width;
    winSize[1] = height;
    graph->resize(winSize[0], winSize[1]);
}
