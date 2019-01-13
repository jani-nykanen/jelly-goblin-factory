// Pause menu
// (c) 2019 Jani Nykänen

#ifndef __PAUSE_H__
#define __PAUSE_H__

#include "../../Menu.hpp"

// Pause class
class PauseMenu {

private:

    // Is active
    bool active;
    
    // Menu
    Menu menu;

    // Box dimensions
    float width;
    float height;
    // Text scale
    float scale;

    // Offsets
    float xoff;
    float yoff;

public:

    // Constructor
    inline PauseMenu() {}
    PauseMenu(std::vector<MenuButton> buttons, 
        float width, float height, float scale);

    // Update
    void update(EventManager* evMan, bool esc=false);
    // Draw
    void draw(Graphics* g, float tx=0, float ty=0);

    // Activate
    void activate(int cpos = 0);
    // Deactive
    void deactivate();

    // Getters
    inline bool isActive() {
        return active;
    }

    // Set button text
    void setButtonText(int button, std::string newText);

};

#endif // __PAUSE_H__
