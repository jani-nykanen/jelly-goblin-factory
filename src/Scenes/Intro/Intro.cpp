// Intro screen scene
// (c) 2019 Jani Nykänen

#include "Intro.hpp"

#include "../Game/Stage.hpp"

#include "../../Core/SceneManager.hpp"

// Constants
static const float WAIT_TIME = 120.0f;

// Reference to self
static Intro* iref;

// Callbacks
static void cb_Title() {
    iref->goToTitle();
}



// Go to the stage menu
void Intro::goToTitle() {

    sceneMan->changeActiveScene("title");
}



// Initialize scene
void Intro::init() {
    
    iref = this;

    // Get "global" objects
    trans = evMan->getTransition();

    // Get bitmaps
    bmpCreator = assets->getBitmap("creator");
    
    // Set defaults
    cogAngle = 0.0f;
    timer = 0.0f;
}


// Update scene
void Intro::update(float tm) {

    const float COG_SPEED = 0.05f;

    // Update cog
    cogAngle += COG_SPEED *tm;

    if(trans->isActive()) return;

    // Update timer
    timer += 1.0f * tm;
    // Check if ready for transition
    GamePad* vpad = evMan->getController();
    if(timer >= WAIT_TIME || 
       vpad->getButton("start") == State::Pressed ||
       vpad->getButton("accept") == State::Pressed) {

        trans->activate(FadeIn, 2.0f, cb_Title, Color(0.1f, 0.60f, 1.0f));
    }
}

    
// Draw scene
void Intro::draw(Graphics* g) {

    const float COG_Y = -96;

    Vector2 view = g->getViewport();

    g->clearScreen(0.1f, 0.60f, 1.0f);

    // Set transform
    g->setView(VIEW_HEIGHT);
    g->identity();
    g->useTransf();
   
    // Draw cog
    g->push();
    g->translate(view.x/2,view.y/2 +COG_Y);
    g->rotate(cogAngle);
    g->useTransf();

    g->drawBitmap(bmpCreator, 0, 0, 256, 256, -128, -128);

    g->pop();
    g->useTransf();

    // Draw face
    g->drawBitmap(bmpCreator, 256, 0, 256, 256, 
        view.x/2-128, 
        view.y/2-128 +COG_Y);

    // Draw text
    g->drawBitmap(bmpCreator, 0, 256, 512, 256, 
        view.x/2-256, 
        view.y/2);
}


// Destroy scene
void Intro::dispose() {
    
    // ...
}


// On change
void Intro::onChange(void* param) {

    // ...
}   
