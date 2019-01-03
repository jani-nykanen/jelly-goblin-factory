// Input listener
// (c) 2019 Jani Nykänen

#ifndef __INPUT_LISTENER_H__
#define __INPUT_LISTENER_H__

#include <vector>

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

public:

    // Constructor
    InputListener();

};

#endif // __INPUTLISTENER_H__
