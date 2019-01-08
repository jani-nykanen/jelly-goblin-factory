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
    bmpParrot = assets->getBitmap("parrot");
    bmpFont = assets->getBitmap("font");

    // Set defaults
    angle = 0.0f;
}


// Update scene
void Game::update(float tm) {

    angle += 0.05f * tm;
    fmodf(angle, M_PI*2);
}


// Draw scene
void Game::draw(Graphics* g) {

    Vector2 view = g->getViewport();

    g->clearScreen(0.75f, 0.75f, 0.75f);

    // Set transform
    g->setView(720.0f);
    g->identity();
    
    g->push();
    g->translate(view.x/2, view.y/2);
    g->rotate(angle);
    float s = sinf(angle)*0.5f + 1.0f;
    g->scale(s, s);
    g->useTransf();

    g->setColor(1, 0, 0, 1.0f);
    g->fillRect(-32, -32, 64, 64);

    g->pop();
    g->useTransf();

    g->setColor(0, 1, 0, 0.25f);
    g->fillRect(view.x/2 - 128, view.y/2-128, 256, 256);

    g->identity();
    g->useTransf();
    g->setColor();
    g->drawBitmap(bmpParrot, 32, 32, 256, 256, Flip::Both);
    g->setColor(1, 0, 0, 0.5f);
    g->drawBitmap(bmpParrot, 192, 192);

    // Draw some text
    g->setColor(1,1,0);
    g->drawText(bmpFont, "Hello world!", view.x/2, 16, -32,0, 1.0f, true);
}


// Dispose scene
void Game::dispose() {

    printf("Terminating...\n");
}


// Called when the scene is changed
// to this scene
void Game::onChange() {

}
