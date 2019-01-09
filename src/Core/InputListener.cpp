// Input listener
// (c) 2019 Jani Nykänen

#include "InputListener.hpp"

#include "MathExt.hpp"

#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdio>

// Maximum amount of joystick buttons
#define MAX_BUTTONS 16

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


// Update joystick hat
void InputListener::updateJoyHat(const uint8* buttons) {

    
}


// Update joystick
void InputListener::updateJoystick(float x, float y) {

    joystick.x = x;
    joystick.y = y;
}


// Constructor
InputListener::InputListener(void* window) {

    // Initialize vectors
    kbstate = std::vector<int> (GLFW_KEY_LAST);
    for(int i = 0; i < kbstate.size(); ++ i) {

        kbstate[i] = State::Up;
    }
    joystate = std::vector<int> (MAX_BUTTONS);
    joybuffer = std::vector<uint8> (MAX_BUTTONS);
    for(int i = 0; i < joystate.size(); ++ i) {

        joystate[i] = State::Up;
        joybuffer[i] = 0;
    }
    
    // Register key event listeners
    self = this;
    if(window != NULL)
        glfwSetKeyCallback((GLFWwindow*)window, keybCallback);

    // Check if joystick is active
    joyActive = glfwJoystickPresent(GLFW_JOYSTICK_1);
    joystick.x = 0;
    joystick.y = 0;
}


// Update input
void InputListener::updateInput() {

    const float DELTA = 0.01f;

    // Update state arrays
    updateInputArray(kbstate);
    updateInputArray(joystate);

    // Update joystick stick
    joystick.x = 0;
    joystick.y = 0;
    if(joyActive) {

        int count;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
        if(count >= 2) {
            
            // Check if enough movement
            if(hypotf(axes[0],axes[1]) > DELTA) {

                updateJoystick(axes[0], axes[1]);
            }
            // Check hat
            if(count >= 6)  {

                if(hypotf(axes[4],axes[5]) > DELTA) {

                    updateJoystick(axes[4], axes[5]);
                }
            }
        }

        // Update joystick buttons
        const uint8* buttons = glfwGetJoystickButtons(
            GLFW_JOYSTICK_1, &count);
        uint8 state=0;
        for(int i = 0; i < max_int32(count, MAX_BUTTONS); ++ i) {

            state = buttons[i];
			if(state != joybuffer[i]) {

				if(state == 1)
					inputDown(joystate, i);
						
				else if(state == 0)
					inputUp(joystate, i);
			}
			joybuffer[i] = state;
        }

        // Update joy hat
        updateJoyHat(buttons);
        
    }
}
