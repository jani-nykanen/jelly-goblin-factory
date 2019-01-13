// A virtual gamepad
// (c) 2019 Jani Nykänen

#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#include "InputListener.hpp"
#include "Types.hpp"

#include <string>

// Gamepad button
struct PadButton {

    int key;
    int button;
    int state;
    std::string name;
    inline PadButton(){}
    inline PadButton(std::string name, int key=-1, int button=-1) {

        this->name = name;
        this->key = key;
        this->button = button;
    }
};

// Gamepad type
class GamePad {

private:

    // Analogue stick
    Vector2 stick;
    // Stick delta
    Vector2 delta;

    // Buttons
    std::vector<PadButton> buttons;

public:

    // Constructors
    inline GamePad() {}
    GamePad(std::string confPath);

    // Update
    void update(InputListener* input);

    // Get button
    int getButton(std::string name);
    // Get stick
    inline Vector2 getStick() {
        return stick;
    }
    // Get stick delta
    inline Vector2 getDelta() {
        return delta;
    }
};

#endif // __GAMEPAD_H__
