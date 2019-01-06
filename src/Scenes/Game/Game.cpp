// Game scene
// (c) 2019 Jani Nykänen

#include "Game.hpp"

#include <cstdio>

#include <GLFW/glfw3.h>


// Initialize scene
void Game::init() {

    printf("Initializing...\n");
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
}


// Dispose scene
void Game::dispose() {

    printf("Terminating...\n");
}


// Called when the scene is changed
// to this scene
void Game::onChange() {

}
