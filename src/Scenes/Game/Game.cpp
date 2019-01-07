// Game scene
// (c) 2019 Jani Nykänen

#include "Game.hpp"

#include "../../Core/MathExt.hpp"

#include <cstdio>
#include <cmath>

#include <GLFW/glfw3.h>


// Initialize scene
void Game::init() {

    printf("Initializing...\n");

    // Load bitmaps
    bmpParrot = new Bitmap("parrot.bin");
    bmpFont = new Bitmap("font.bin");
}


// Update scene
void Game::update(int steps) {

    angle += 1 * steps;
    angle %= 360;
}


// Draw scene
void Game::draw(Graphics* g) {

    g->clearScreen(0b10010010);

    FixedPoint c = fixedCos(angle)/2 + FIXED_PRECISION;
    FixedPoint s = fixedSin(angle)/2 + FIXED_PRECISION;

    g->drawPseudo3DFloor(bmpParrot, 
        Vec2Fixed(160, 100), 
        Vec2Fixed(c, s, false), 
        angle, 0);

    // Draw text
    g->drawText(bmpFont, "Hello world!", 2, 2, -4, 0);
}


// Dispose scene
void Game::dispose() {

    printf("Terminating...\n");
}


// Called when the scene is changed
// to this scene
void Game::onChange() {

}
