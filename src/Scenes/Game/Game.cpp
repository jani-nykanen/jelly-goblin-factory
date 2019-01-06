// Game scene
// (c) 2019 Jani Nykänen

#include "Game.hpp"

#include <cstdio>

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

}


// Draw scene
void Game::draw(Graphics* g) {

    g->clearScreen(0b10010010);

    // Draw palette
    int x, y;
    for(int i = 0; i < 256; ++ i) {

        x = (i%16) * 8;
        y = i / 16; y *= 8;

        g->fillRect(x, y, 8, 8, (uint8)i);
        
    }

    // Draw parrot
    g->drawBitmap(bmpParrot,0, 0, 128, 128, 224, -32, Flip::Both);

    // Draw text
    g->drawText(bmpFont, "Hello world!", 2, 180, -4, 0);
}


// Dispose scene
void Game::dispose() {

    printf("Terminating...\n");
}


// Called when the scene is changed
// to this scene
void Game::onChange() {

}
