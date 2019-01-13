// A virtual gamepad
// (c) 2019 Jani Nykänen

#include "GamePad.hpp"

#include "Config.hpp"

#include "GLFW/glfw3.h"

#include <sstream>
#include <cmath>


// Parse CSV with 2 values
static void parseCSV(std::string str, int &left, int&right) {

    // Find ","
    int commaPos = 0;
    for(int i = 0; i < str.length(); ++ i) {

        if(str[i] == ',') {

            commaPos = i;
            break;
        }
    }

    // Get left & right strings
    std::string lstr = str.substr(0, commaPos);
    std::string rstr = str.substr(commaPos+1);

    std::istringstream(lstr) >> left;
    std::istringstream(rstr) >> right;
}


// Constructor
GamePad::GamePad(std::string confPath) {

    buttons = std::vector<PadButton> ();

    // Read key configuration
    ConfigData conf = ConfigData(confPath);

    // Get buttons
    int key, button;
    std::string name;
    for(int i = 0; i < conf.getParamCount(); ++ i) {

        // Get data
        parseCSV(conf.getParam(i), key, button);
        name = conf.getKey(i);

        // Add
        buttons.push_back(PadButton(name, key, button));
    }
}


// Update
void GamePad::update(InputListener* input) {
    
    const float DELTA = 0.01f;

    // Update buttons
    for(int i = 0; i < buttons.size(); ++ i) {

        // Check key
        buttons[i].state = input->getKeyState(buttons[i].key);
        // Check joystick button
        if(buttons[i].state == State::Up) {

            buttons[i].state = 
                input->getButtonState(buttons[i].button);
        }
    }

    // Update stick
    Vector2 oldStick = stick;
    // Check joystick
    stick = input->getJoystick();
    // Check keyboard
    if(input->getKeyState(GLFW_KEY_LEFT) == State::Down)
        stick.x = -1;
    else if(input->getKeyState(GLFW_KEY_RIGHT) == State::Down)
        stick.x = 1;
    if(input->getKeyState(GLFW_KEY_UP) == State::Down)
        stick.y = -1;
    else if(input->getKeyState(GLFW_KEY_DOWN) == State::Down)
        stick.y = 1;

    // Make sure not beyond B(0,1)
    if(fabsf(stick.x)-fabsf(stick.y) < DELTA 
        && fabsf(stick.x) >= 1.0f-DELTA) {

        stick.x *= 0.707f;
        stick.y *= 0.707f;
    }

    // Compute delta
    delta.x = stick.x - oldStick.x;
    delta.y = stick.y - oldStick.y;
}


// Get button
int GamePad::getButton(std::string name) {
    
    for(int i = 0; i < buttons.size(); ++ i) {

        if(buttons[i].name == name) {

            return buttons[i].state;
        }
    }
    return State::Up;
}
