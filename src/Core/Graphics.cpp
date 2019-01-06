// Graphics context & routines
// (c) 2019 Jani Nykänen

#include "Graphics.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <cstring>

// Constructor
Graphics::Graphics(int canvasWidth, int canvasHeight) 
    : GraphicsCore(canvasWidth, canvasHeight) {

    // ...
}


// Clear screen
void Graphics::clearScreen(uint8 color) {

    memset(canvasFramebuffer, color, canvasWidth*canvasHeight);
}
