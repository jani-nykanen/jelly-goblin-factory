// Ending scene
// (c) 2019 Jani Nykänen

#include "Ending.hpp"

#include "../Game/Stage.hpp"

#include "../../Core/SceneManager.hpp"

// Constants
static float ENDING_TIME = 480.0f;

// Reference to self
static Ending* eref;

// Ending texts
static const char ENDING1[] = 
    "Congratulations! You have earned\n"
    "the silver trophy. Collect the\n"
    "remaining stars to obtain the\n"
    "the golden one!";
static const char ENDING2[] = 
    "Congratulations! You have earned\n"
    "the golden trophy. Now, go\n"
    "outside and... GET A LIFE!";


// Callbacks
static void cb_Back() {
    eref->back();
}


// Back to stage menu
void Ending::back() {

    sceneMan->changeActiveScene("stageMenu");
}


// Initialize scene
void Ending::init() {
    
    eref = this;

    // Get "global" objects
    trans = evMan->getTransition();

    // Get bitmaps
    bmpFont = assets->getBitmap("font");
    bmpTrophy = assets->getBitmap("trophy");
    // Get samples
    sAccept = assets->getSample("accept");

    // Set ending text
    endingText[0] = std::string(ENDING1);
    endingText[1] = std::string(ENDING2);

    // Set defaults
    endingTimer = 0.0f;
    complMode = 0;
}


// Update scene
void Ending::update(float tm) {

    if(trans->isActive()) return;

    GamePad* vpad = evMan->getController();
    AudioManager* audio = evMan->getAudioManager();

    // Update ending timer
    if(endingTimer > 0.0f) {

        endingTimer -= 1.0f * tm;
        if(endingTimer < 0.0f)
            endingTimer = 0.0f;
    }
    // If enter pressed, quit
    else if(vpad->getButton("start") == State::Pressed) {

        // Play sound
        audio->playSample(sAccept, 0.45f);

        trans->activate(FadeIn, 2.0f, cb_Back);
    }

}

    
// Draw scene
void Ending::draw(Graphics* g) {

    const float TROPHY_SCALE = 1.5f;
    const float TROPHY_YOFF = -64.0f;

    const float TEXT_X = -400.0f;
    const float TEXT_Y = 144.0f;
    const float XOFF = -32.0f;
    const float YOFF = -6.0f;
    const float SHADOW_X = 4;
    const float SHADOW_Y = 6;
    const float SHADOW_ALPHA = 0.5f;
    const float TEXT_SCALE = 0.75f;

    Vector2 view = g->getViewport();

    g->clearScreen(0.1f, 0.60f, 1.0f);

    // Set transform
    g->setView(VIEW_HEIGHT);
    g->identity();
    g->useTransf();

    // Draw trophy
    float x = view.x/2-128.0f*TROPHY_SCALE;
    float y = view.y/2-128.0f*TROPHY_SCALE + TROPHY_YOFF;
    g->drawBitmap(bmpTrophy, complMode*256, 0, 256, 256,
        x, y, 256*TROPHY_SCALE, 256*TROPHY_SCALE);

    // Compute character position
    std::string s = endingText[complMode];
    float t = 1.0f - (endingTimer / ENDING_TIME);
    int cpos = (int)(t * (float)s.length());

    // Draw text
    g->drawText(bmpFont, s.substr(0, cpos), 
        view.x/2+TEXT_X, view.y/2+TEXT_Y, 
        XOFF, YOFF, SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
        TEXT_SCALE, false);
}


// Destroy scene
void Ending::dispose() {
    
    // ...
}


// On change
void Ending::onChange(void* param) {

    endingTimer = ENDING_TIME;
    complMode = (int)(size_t)param;
}   
