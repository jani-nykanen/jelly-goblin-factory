// Input listener
// (c) 2019 Jani Nykänen

#ifndef __INPUT_LISTENER_H__
#define __INPUT_LISTENER_H__

#include <vector>

#include "Types.hpp"

// Key states
namespace State {

    enum {
        Up = 0,
        Down = 1,
        Pressed = 2,
        Released = 3,
    };
}


// Input listener class
class InputListener {

protected:

    // Keyboard states
    std::vector<int> kbstate;
    // Joy buttons
    std::vector<int> joystate;
    // Joystick button buffer
    std::vector<uint8> joybuffer;

    // Joystick
    Vector2 joystick;
    // Is joystick active
    bool joyActive;

    // Input down
    void inputDown(std::vector<int> &arr, int index);
    // Input up
    void inputUp(std::vector<int> &arr, int index);
    // Update input array
    void updateInputArray(std::vector<int> &arr);
    // Get input state
    int getInputState(std::vector<int> arr, int index);

    // Update joystick hat
    void updateJoyHat(const uint8* buttons);

public:

    // Keyboard events
    inline void keyDown(int key){ inputDown(kbstate, key); }
    inline void keyUp(int key){ inputUp(kbstate, key); }

    // Update joystick
    void updateJoystick(float x, float y);

    // Constructor
    InputListener(void* window);

    // Update input
    void updateInput();

    // Get input states
    inline int getKeyState(int key) { return getInputState(kbstate, key); }
    inline int getButtonState(int b) { return getInputState(joystate, b); }
    // Get joystick
    inline Vector2 getJoystick() {return joystick;}

};

#endif // __INPUTLISTENER_H__
