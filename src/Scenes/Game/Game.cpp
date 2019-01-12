// Game scene
// (c) 2019 Jani Nykänen

#include "Game.hpp"

#include "../../Core/MathExt.hpp"
#include "../../Core/Tilemap.hpp"

#include <cstdio>
#include <cmath>

#include <GLFW/glfw3.h>


// Reset the current game state
void Game::reset() {

    // Reset stage
    stage->reset();
    // Reset hud
    hud.reset();

    // Reset workers
    workers.clear();
    stage->parseMap(comm);
}


// Initialize scene
void Game::init() {

    printf("Initializing...\n");

    // Get bitmaps
    bmpFont = assets->getBitmap("font");

    // Create communicator
    comm = Communicator(this);

    // Initialize global data
    initGlobalStage(assets);
    initGlobalWorker(assets);

    // Initialize stage
    stage = new Stage("Assets/Tilemaps/test.tmx");
    // Parse map for objects
    workers = std::vector<Worker> ();
    stage->parseMap(comm);

    // Initialize HUD
    hud = Hud(assets);
    hud.setMoveTarget(stage->getMoveTarget());
}


// Update scene
void Game::update(float tm) {

    // Reset
    if(evMan->getController()->getButton("reset") == State::Pressed) {

        reset();
    }

    // "Pre-update"
    bool anyMoving = false;
    for(int i = 0; i < workers.size(); ++ i) {

        // Check cog collisions
        workers[i].checkCogCollision(stage);

        // Is moving
        if(!anyMoving && workers[i].isActive()) {

            anyMoving = true;
        }
    }


    // Update workers
    bool anyStartedMoving = false;
    for(int i = 0; i < workers.size(); ++ i) {

        workers[i].update(evMan, stage, anyMoving, tm);
        if(!anyStartedMoving && workers[i].hasStartedMoving())
            anyStartedMoving = true;
    }
    // Increase turns, if moved
    if(anyStartedMoving)
        hud.addMove();

    // Update stage
    stage->update(evMan, tm);

    // Update HUD
    hud.update();
}


// Draw scene
void Game::draw(Graphics* g) {

    g->clearScreen(0.1f, 0.60f, 1.0f);

    // Set transform
    g->setView(720.0f);
    g->identity();
    g->useTransf();

    // Draw stage
    stage->draw(g, comm);

    // Draw hud
    hud.draw(g);
}


// Dispose scene
void Game::dispose() {

    delete stage;

    printf("Terminating...\n");
}


// Called when the scene is changed
// to this scene
void Game::onChange() {

    // ...
    
}


// Draw workers
void Game::drawWorkers(Graphics* g) {

    // Draw workers
    for(int i = 0; i < workers.size(); ++ i) {

        workers[i].draw(g);
    }
}


// Add a worker
void Game::addWorker(Point p, int color,  
    bool sleeping, bool isCog) {

    workers.push_back(Worker(p, color, sleeping, isCog));
}
