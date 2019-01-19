// A simple menu
// (c) 2019 Jani Nykänen

#include "Menu.hpp"

#include <cstdlib>

// Bitmaps
static Bitmap* bmpFont;
// Samples
static Sample* sSelect;
static Sample* sAccept;


// Constructor
Menu::Menu(std::vector<MenuButton> buttons) {

    // Store data
    this->buttons = buttons;
    count = buttons.size();

    // Set defaults
    cursorPos = 0;
}


// Update
void Menu::update(EventManager* evMan) {

    Transition* trans = evMan->getTransition();

    const float DELTA = 0.25f;

    // Get audio manager
    AudioManager* audio = evMan->getAudioManager();

    // Get gamepad
    GamePad* vpad = evMan->getController();
    float sticky = vpad->getStick().y;
    float deltay = vpad->getDelta().y;

    // Update cursor position
    int oldp = cursorPos;
    if(sticky < -DELTA && deltay < -DELTA) {

        if(-- cursorPos < 0)
            cursorPos += count;
    }
    else if(sticky > DELTA && deltay > DELTA) {

        if(++ cursorPos >= count)
            cursorPos -= count;
    }
    // Play sound, if changed
    if(oldp != cursorPos) {

        audio->playSample(sSelect, 0.70f);
    }

    // Check key press
    MenuButton b;
    if(vpad->getButton("accept") == State::Pressed ||
       vpad->getButton("start") == State::Pressed) {

        // Call callback function, if any
        b = buttons[cursorPos];
        MenuCallback cb = b.cb;
        if(cb != NULL) {

            if(b.useTransition) {

                trans->activate(FadeIn, b.transSpeed, cb);
            }
            else {
                cb();
            }
        }

        // Play sound
        audio->playSample(sAccept, 0.45f);
    }
}


// Draw
void Menu::draw(Graphics* g, float x, float y, 
    float scale,  float yoff) {

    const float XOFF = MENU_TEXT_XOFF;
    const float BASE_YOFF = MENU_TEXT_YOFF;

    const float SHADOW_X = 4*scale;
    const float SHADOW_Y = 6*scale;
    const float SHADOW_TRANS = 0.5f;

    // Draw buttons
    std::string text;
    float h = bmpFont->getWidth()/16.0f;
    for(int i = 0; i < count; ++ i) {

        text = i == cursorPos ? ">" : "";
        text += buttons[i].text;

        // Set color
        if(i == cursorPos)
            g->setColor(1, 1, 0);
        else
            g->setColor();

        // Draw text
        g->drawText(bmpFont, text, 
            x, y + i*(h+BASE_YOFF+yoff)*scale, 
            XOFF, 0, 
            SHADOW_X, SHADOW_Y,SHADOW_TRANS,
            scale);
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
    // Get samples
    sSelect = assets->getSample("select");
    sAccept = assets->getSample("accept");
}

