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
    void update(EventManager* evMan);
    // Draw
    void draw(Graphics* g);

    // Activate
    void activate();
    // Deactive
    void deactivate();

    // Getters
    inline bool isActive() {
        return active;
    }

};

#endif // __PAUSE_H__
