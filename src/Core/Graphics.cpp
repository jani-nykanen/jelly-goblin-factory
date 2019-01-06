// Graphics context & routines
// (c) 2019 Jani Nykänen

#include "Graphics.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <cstring>
#include <cstdio>


// Clip
bool Graphics::clip(int &x, int &y, int &w, int &h) {

    int dif;

    // Check if we have anything to draw
    if(x+w < 0 || x >= canvasWidth || y+h <= 0 || y >= canvasHeight)
        return false;

    // Clip X
    if(x < 0) {

        dif = -x;
        x = 0;
        w -= dif;
    }
    if(x+w >= canvasWidth) {

        dif = canvasWidth-(x+w);
        w += dif;
    }

    // Clip Y
    if(y < 0) {

        dif = -y;
        y = 0;
        h -= dif;
    }
    if(y+h >= canvasHeight) {

        dif = canvasHeight-(y+h);
        h += dif;
    }

    return true;
}


// Constructor
Graphics::Graphics(int canvasWidth, int canvasHeight) 
    : GraphicsCore(canvasWidth, canvasHeight) {

    // ...
}


// Clear screen
void Graphics::clearScreen(uint8 color) {

    memset(frame->getData(), color, canvasWidth*canvasHeight);
}


// Draw a filled rectangle
void Graphics::fillRect(int x, int y, int w, int h, uint8 color) {

    uint8* d = frame->getData();
    int fw = frame->getWidth();

    if(!clip(x, y, w, h)) return;

    // Copy rectangle lines to the framebuffer
    int offset = y*fw + x;
    for(int i = 0; i < h; ++ i) {

        memset((uint8*)(d + offset), color, w);
        offset += fw;
    }
}
