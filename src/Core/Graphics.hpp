// Graphics context & routines
// (c) 2019 Jani Nykänen

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "GraphicsCore.hpp"


// Graphics class
class Graphics : public GraphicsCore {

private:

    // Clip
    bool clip(int &x, int &y, int &w, int &h);

public:

    // Constructor
    Graphics(int canvasWidth, int canvasHeight);

    // Clear screen
    void clearScreen(uint8 color);

    // Draw a filled rectangle
    void fillRect(int x, int y, int w, int h, uint8 color);
};

#endif // __GRAPHICS_H__
