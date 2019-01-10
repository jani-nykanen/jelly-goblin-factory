// Game scene
// (c) 2019 Jani Nykänen

#include "Game.hpp"

#include "../../Core/MathExt.hpp"
#include "../../Core/Tilemap.hpp"

#include <cstdio>
#include <cmath>

#include <GLFW/glfw3.h>


// Initialize scene
void Game::init() {

    printf("Initializing...\n");

    // Get bitmaps
    bmpFont = assets->getBitmap("font");

    // Initialize global data
    initGlobalStage(assets);

    // Initialize stage
    stage = new Stage("Assets/Tilemaps/test.tmx");
}


// Update scene
void Game::update(float tm) {

    stage->update(evMan, tm);
}


// Draw scene
void Game::draw(Graphics* g) {

    g->clearScreen(0.1f, 0.60f, 1.0f);

    // Set transform
    g->setView(720.0f);
    g->identity();
    g->useTransf();

    // Draw stage
    stage->draw(g);

    // Draw temporary text
    g->setColor();
    g->drawText(bmpFont, "Stage 0", 16, 16, -32, 0,
        4.0f, 6.0f, 0.5f,
     1.0f, false);
}


// Dispose scene
void Game::dispose() {

    delete stage;

    printf("Terminating...\n");
}


// Called when the scene is changed
// to this scene
void Game::onChange() {

    
}
