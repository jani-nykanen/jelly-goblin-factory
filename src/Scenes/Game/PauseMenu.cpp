// Pause menu
// (c) 2019 Jani Nykänen

#include "PauseMenu.hpp"


// Constructor
PauseMenu::PauseMenu(std::vector<MenuButton> buttons, 
        float width, float height, float scale) {

    // Store data
    menu = Menu(buttons);
    this->width = width;
    this->height = height;
    this->scale = scale;

    // Set defaults
    active = false;

    // Compute max string length
    int max = buttons[0].text.length() +1;
    int b;
    for(int i = 1; i < buttons.size(); ++ i) {

        b = buttons[i].text.length() +1;
        if(b > max) {

            max = b;
        }
    }
    // Compute offsets
    xoff = width/2 - max*(64.0f+MENU_TEXT_XOFF)/2.0f*scale;
    yoff = height/2 - (buttons.size())*(64.0f+MENU_TEXT_YOFF)/2.0f*scale;
}


// Update
void PauseMenu::update(EventManager* evMan, bool esc) {
    
    if(!active) return;

    // Quit with escape, if enabled
    if(esc
    && evMan->getController()->getButton("cancel") == State::Pressed) {

        deactivate();
        return;
    }

    // Update menu
    menu.update(evMan);
}


// Draw
void PauseMenu::draw(Graphics* g, float tx, float ty) {
    
    const float DARKEN_ALPHA = 0.25f;
    const float BOX_ALPHA = 0.75f;

    if(!active) return;

    // Darken the game screen
    Vector2 view = g->getViewport();
    g->setColor(0, 0, 0, DARKEN_ALPHA);
    g->fillRect(0, 0, view.x, view.y);

    g->push();
    g->translate(tx, ty);
    g->useTransf();

    // Draw box
    float x = view.x/2 - width/2;
    float y = view.y/2 - height/2;
    g->setColor(0, 0, 0, BOX_ALPHA);
    g->fillRect(x, y, width, height);

    // Draw menu
    menu.draw(g, x + xoff, y + yoff, scale);

    g->pop();
    g->useTransf();
}


// Activate
void PauseMenu::activate(int cpos) {

    active = true;
    if(cpos >= 0)
        menu.setCursorPos(cpos);
}


// Deactivate
void PauseMenu::deactivate() {

    active = false;
}


// Set button text
void PauseMenu::setButtonText(int button, 
    std::string newText) {

    menu.setText(button, newText);
}
