// Graphics context & routines
// (c) 2019 Jani Nykänen

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "GraphicsCore.hpp"

// Flipping flags
namespace Flip {

    enum {

        None = 0,
        Horizontal = 1,
        Vertical = 2,
        Both = Horizontal | Vertical,
    };
}


// Graphics class
class Graphics : public GraphicsCore {

private:

public:

    // Constructor
    Graphics();

    // Clear screen
    void clearScreen(float r, float g, float b);
    
    // Set color
    void setColor(float r = 1, float g = 1, float b = 1, float a = 1);
    
    // Draw a filled rectangle
    void fillRect(float x, float y, float w, float h);
};

#endif // __GRAPHICS_H__
