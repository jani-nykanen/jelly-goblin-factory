// Input listener
// (c) 2019 Jani Nykänen

#include "InputListener.hpp"

#include <GLFW/glfw3.h>

// Reference to self
static InputListener* self;


// Keyboard callback
static void keybCallback(GLFWwindow* window, 
    int key, int scancode, int action, int mods) {

    // Key pressed
    if(action == GLFW_PRESS) {

        self->keyDown(key);
    }
    else if(action == GLFW_RELEASE) {

        self->keyUp(key);
    }
}


// Input down
void InputListener::inputDown(std::vector<int> &arr, int index) {

    if(index < 0 || index >= arr.size() 
    || arr[index] == State::Down)
        return;

    arr[index] = State::Pressed;
}


// Input up
void InputListener::inputUp(std::vector<int> &arr, int index) {

    if(index < 0 || index >= arr.size() 
    || arr[index] == State::Up)
        return;

    arr[index] = State::Released;
}


// Update input array
void InputListener::updateInputArray(std::vector<int> &arr) {

    for(int i = 0; i < arr.size(); ++ i) {

        if(arr[i] == State::Pressed)
            arr[i] = State::Down;

        else if(arr[i] == State::Released)
            arr[i] = State::Up;
    }
}


// Get input array state
int InputListener::getInputState(std::vector<int> arr, int index) {

    if(index < 0 || index >= arr.size()) 
        return State::Up;

    return arr[index];
}


// Constructor
InputListener::InputListener(void* window) {

    // Initialize vectors
    kbstate = std::vector<int> (GLFW_KEY_LAST);
    for(int i = 0; i < kbstate.size(); ++ i) {

        kbstate[i] = State::Up;
    }
    
    // Register key event listeners
    self = this;
    if(window != NULL)
        glfwSetKeyCallback((GLFWwindow*)window, keybCallback);
}


// Update input
void InputListener::updateInput() {

    // Update state arrays
    updateInputArray(kbstate);
}
