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

// Draw "Stage clear"
void Game::drawStageClear(Graphics* g) {

    const float END_MENU_Y = 128.0f;
    const float SHADOW_X = 4.0f;
    const float SHADOW_Y = 6.0f;
    const float SHADOW_ALPHA = 0.5f;
    const float TEXT_Y = -96;
    const float XOFF = -32.0f;
    const float BASE_SCALE = 1.5f;
    const float SCALE_MOD = 0.25f;
    const float COLOR_MOD = 0.25f;

    Vector2 view = g->getViewport();

    // Draw end menu
    endMenu.draw(g, 0, END_MENU_Y);

    // Compute size & color mods
    float s = sinf(endTimer);
    float scale = BASE_SCALE + s*SCALE_MOD;
    float cmod = (s+1.0f)/2.0f * COLOR_MOD;

    // Draw "Stage clear"
    if(hud.isPerfectClear())
        g->setColor(1.5f+cmod,1.5f+cmod,0.5f+cmod);
    else
        g->setColor(0.65f+cmod,0.65f+cmod,0.65f+cmod);

    g->drawText(bmpFont, "STAGE CLEAR!", 
        view.x/2, view.y/2 + TEXT_Y*(1+s*SCALE_MOD/2), XOFF, 0, 
        SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
        scale, true);
}


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
    endMenu.deactivate();
}


// Resume game
void Game::resume() {

    pause.deactivate();
}


// Terminate
void Game::terminate() {
    
    pause.deactivate();
    endMenu.deactivate();
    evMan->terminate();
}


// Initialize scene
void Game::init() {

    const float PAUSE_WIDTH = 384.0f;
    const float PAUSE_HEIGHT = 288.0f;
    const float PAUSE_SCALE = 1.0f;

    const float END_WIDTH = 320.0f;
    const float END_HEIGHT = 160.0f;
    const float END_SCALE = 0.75f;

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
        PAUSE_WIDTH, PAUSE_HEIGHT, PAUSE_SCALE);

    // Create end menu
    buttons.clear();
    buttons.push_back(MenuButton("Next stage", cb_Reset));
    buttons.push_back(MenuButton("Retry", cb_Reset));
    buttons.push_back(MenuButton("Stage menu", cb_Terminate));
    endMenu = PauseMenu(buttons, 
        END_WIDTH, END_HEIGHT, END_SCALE);
}


// Update scene
void Game::update(float tm) {

    const float END_TIMER_SPEED = 0.05f;

    GamePad* vpad = evMan->getController();

    // Check end menu
    if(endMenu.isActive()) {

        // Update end menu
        endMenu.update(evMan);

        // Update end timer
        endTimer += END_TIMER_SPEED * tm;
        endTimer = fmodf(endTimer, M_PI *2.0f);

        return;
    }
    // TEMP
    else if(vpad->getButton("debug") == State::Pressed) {

        endMenu.activate();
    }

    // Check pause
    if(pause.isActive()) {

        pause.update(evMan, true);
        return;
    }
    else {

        if(vpad->getButton("start") == State::Pressed ||
           vpad->getButton("cancel") == State::Pressed) {

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
    int aliveCount = 0;
    for(int i = 0; i < workers.size(); ++ i) {

        // Check cog collisions
        workers[i].checkCogCollision(stage);

        // Is moving
        if(!anyMoving && workers[i].isActive()) {

            anyMoving = true;
        }

        // If "alive"
        if(workers[i].isAlive()) {

            ++ aliveCount;
        }
    }

    // Check if victory
    if(aliveCount == 0 && !anyMoving) {

        endMenu.activate();
        return;
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
    if(endMenu.isActive()) {

        drawStageClear(g);
    }
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
