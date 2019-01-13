// Game scene
// (c) 2019 Jani Nykänen

#include "Game.hpp"

#include "../../Core/MathExt.hpp"
#include "../../Core/Tilemap.hpp"

#include <cstdio>
#include <cmath>

#include <GLFW/glfw3.h>

// Reference to this
static Game* gref;


// Callbacks
static void cb_Resume() { gref->resume(); }
static void cb_Reset() { gref->reset(); }
static void cb_Terminate() { gref->terminate(); }


// Reset the current game state
void Game::reset() {

    // Reset stage
    stage->reset();
    // Reset hud
    hud.reset();

    // Reset workers
    workers.clear();
    stage->parseMap(comm);

    // Disable pause
    pause.deactivate();
}


// Resume game
void Game::resume() {

    pause.deactivate();
}


// Terminate
void Game::terminate() {
    
    pause.deactivate();
    evMan->terminate();
}


// Initialize scene
void Game::init() {

    const float PAUSE_WIDTH = 384.0f;
    const float PAUSE_HEIGHT = 288.0f;

    printf("Initializing...\n");

    gref = this;

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

    // Create pause menu
    std::vector<MenuButton> buttons;
    buttons.push_back(MenuButton("Resume", cb_Resume));
    buttons.push_back(MenuButton("Restart", cb_Reset));
    buttons.push_back(MenuButton("Settings", NULL));
    buttons.push_back(MenuButton("Quit", cb_Terminate));
    pause = PauseMenu(buttons, 
        PAUSE_WIDTH, PAUSE_HEIGHT, 1.0f);
}


// Update scene
void Game::update(float tm) {

    GamePad* vpad = evMan->getController();

    // Check pause
    if(pause.isActive()) {

        pause.update(evMan);
        return;
    }
    else {

        if(vpad->getButton("start") == State::Pressed) {

            pause.activate();
            return;
        }
    }

    // Reset
    if(vpad->getButton("reset") == State::Pressed) {

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
    g->setView(VIEW_HEIGHT);
    g->identity();
    g->useTransf();

    // Draw stage
    stage->draw(g, comm);

    // Draw hud
    hud.draw(g);

    // Draw pause
    pause.draw(g);
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
