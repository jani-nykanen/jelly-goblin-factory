// A simple menu
// (c) 2019 Jani Nykänen

#ifndef __MENU_H__
#define __MENU_H__

#include "Core/Graphics.hpp"
#include "Core/EventManager.hpp"
#include "Core/AssetPack.hpp"

#include <cstring>
#include <vector>

// Callback type
typedef void (*MenuCallback) (void);

// Menu button
struct MenuButton {

    std::string text;
    MenuCallback cb;

    // Constructors
    inline MenuButton() {}
    inline MenuButton(std::string text, MenuCallback cb) {
        this->text = text;
        this->cb = cb;
    }
};

// Menu class
class Menu {

private:

    // Buttons
    std::vector<MenuButton> buttons;

    // Element count (=buttons.size())
    int count;
    // Cursor position
    int cursorPos;

public:

    // Constructor
    inline Menu() {}
    Menu(std::vector<MenuButton> buttons);

    // Update
    void update(EventManager* evMan);
    // Draw
    void draw(Graphics* g, float x, float y, float scale);

    // Setters
    inline void setCursorPos(int p) {
        cursorPos = p % count;
    }
    // Set button text
    void setText(int p, std::string text);

    // Getters
    inline int getCursorPos() {
        return cursorPos;
    }
};

// Initialize global content
void initGlobalMenu(AssetPack* assets);


#endif // __MENU_H__
