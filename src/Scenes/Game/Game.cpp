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
}


// Update scene
void Game::update(float tm) {


}


// Draw scene
void Game::draw(Graphics* g) {

    g->clearScreen(0.75f, 0.75f, 0.75f);

    g->setColor(1, 0, 0, 1.0f);
    g->fillRect(0, 0, 1, 1);
}


// Dispose scene
void Game::dispose() {

    printf("Terminating...\n");
}


// Called when the scene is changed
// to this scene
void Game::onChange() {

}
