// A simple menu
// (c) 2019 Jani Nykänen

#include "Menu.hpp"

#include <cstdlib>

// Bitmaps
static Bitmap* bmpFont;


// Constructor
Menu::Menu(std::vector<MenuButton> buttons) {

    this->buttons = buttons;
    count = buttons.size();
    cursorPos = 0;
}


// Update
void Menu::update(EventManager* evMan) {

    const float DELTA = 0.25f;

    GamePad* vpad = evMan->getController();
    float sticky = vpad->getStick().y;
    float deltay = vpad->getDelta().y;

    // Update cursor position
    if(sticky < -DELTA && deltay < -DELTA) {

        if(-- cursorPos < 0)
            cursorPos += count;
    }
    else if(sticky > DELTA && deltay > DELTA) {

        if(++ cursorPos >= count)
            cursorPos -= count;
    }

    // Check key press
    if(vpad->getButton("accept") == State::Pressed ||
       vpad->getButton("start") == State::Pressed) {

        // Call callback function, if any
        MenuCallback cb = buttons[cursorPos].cb;
        if(cb != NULL) {

            cb();
        }
    }
}


// Draw
void Menu::draw(Graphics* g, float x, float y, float scale) {

    const float XOFF = -32.0f;
    const float YOFF = -8.0f;

    // Draw buttons
    std::string text;
    float h = bmpFont->getWidth()/16.0f;
    for(int i = 0; i < count; ++ i) {

        text = i == cursorPos ? ">" : "";
        text += buttons[i].text;

        g->drawText(bmpFont, text, x, y + i*(h+YOFF)*scale, XOFF,0, scale);
    }
}


// Set button text
void Menu::setText(int p, std::string text) {
    
    if(p < 0 || p >= count) return;

    buttons[p].text = text;
}


// Initialize global content
void initGlobalMenu(AssetPack* assets) {

    // Get bitmaps
    bmpFont = assets->getBitmap("font");
}

