// Input listener
// (c) 2019 Jani Nykänen

#include "InputListener.hpp"

// Constants
static const int MAX_KEY = 255;


// Constructor
InputListener::InputListener() {

    // Initialize vectors
    kbstate = std::vector<int> (MAX_KEY);
    for(int i = 0; i < kbstate.size(); ++ i) {

        kbstate[i] = State::Up;
    }
}
