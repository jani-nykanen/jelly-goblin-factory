// Event manager
// (c) 2019 Jani Nykänen

#ifndef __EVMAN_H__
#define __EVMAN_H__

#include "InputListener.hpp"
#include "GamePad.hpp"
#include "Transition.hpp"
#include "AudioManager.hpp"

class Application;

// Event manager class
class EventManager : public InputListener {

private:

    // Reference to application
    Application* appRef;
    // Gamepad reference
    GamePad* vpad;
    // Audio manager
    AudioManager* audio;

    // Transition
    Transition trans;

public:

    // Constructor
    EventManager(Application* ref, void* window, GamePad* vpad);
    // Destructor
    ~EventManager();

    // Redirect to application core
    void terminate();
    void toggleFullscreen();

    // Get controller
    inline GamePad* getController() {

        return vpad;
    }
    // Get transition object
    inline Transition* getTransition() {

        return &trans;
    }
    // Get audio manager
    inline AudioManager* getAudioManager() {

        return audio;
    }

};

#endif // __EVMAN_H__
