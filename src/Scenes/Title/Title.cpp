// Title screen scene
// (c) 2019 Jani Nykänen

#include "Title.hpp"

#include "../Game/Stage.hpp"

#include "../../Core/SceneManager.hpp"

// Reference to self
static Title* tref;

// Callbacks
static void cb_Play() {
    tref->goToStageMenu();
}
static void cb_Terminate() {
    tref->terminate();
}


// Go to the stage menu
void Title::goToStageMenu() {

    sceneMan->changeActiveScene("stageMenu");
}


// Initialize scene
void Title::init() {
    
    tref = this;

    // Get "global" objects
    trans = evMan->getTransition();

    // Get bitmaps
    bmpFont = assets->getBitmap("font");
    bmpLogo = assets->getBitmap("logo");
    // Get samples
    sPause = assets->getSample("pause");
    sReject = assets->getSample("reject");

    // Create menu
    std::vector<MenuButton> buttons;
    buttons.push_back(MenuButton("Play", cb_Play, true, 2.0f));
    buttons.push_back(MenuButton("Settings", NULL));
    buttons.push_back(MenuButton("Clear Data", NULL));
    buttons.push_back(MenuButton("Quit", cb_Terminate, true, 2.0f));
    menu = Menu(buttons);

    // Set defaults
    logoFloat = 0.0f;
    logoScale = 0.0f;
    phase = 0;
    enterTimer = -M_PI/2.0f;
}


// Update scene
void Title::update(float tm) {

    const float LOGO_FLOAT = 0.05f;
    const float ENTER_TIMER_SPEED = 0.05f;

    // Update logo scale using
    // transition object
    float t = 1.0f-trans->getTime();
    if(logoScale < t) {

        logoScale = t;
    }

    if(trans->isActive()) return;

    GamePad* vpad = evMan->getController();
    AudioManager* audio = evMan->getAudioManager();

    // Update logo float
    logoFloat += LOGO_FLOAT * tm;
    logoFloat = fmodf(logoFloat, M_PI*4.0f);

    if(phase == 1) {

        // Update menu
        menu.update(evMan);
    }
    else {
        
        // Update timer
        enterTimer += ENTER_TIMER_SPEED * tm;
        enterTimer = fmodf(enterTimer, M_PI*2);

        // Check enter
        if(vpad->getButton("start") == State::Pressed ||
            vpad->getButton("accept") == State::Pressed) {

            // Play sound
            audio->playSample(sPause, 0.40f);

            // Next phase
            ++ phase;
        }
    }

    // Check escape
    if(vpad->getButton("cancel") == State::Pressed) {

        audio->playSample(sReject, 0.40f);
        trans->activate(FadeIn, 2.0f, cb_Terminate);
    }
}

    
// Draw scene
void Title::draw(Graphics* g) {

    const float LOGO_SCALE = 1.5f;
    const float LOGO_SHADOW_X = 12.0f;
    const float LOGO_SHADOW_Y = 16.0f;
    const float LOGO_AMPLITUDE = 16.0f;
    const float SCALE_MOD = 0.05f;

    const float TEXT_X = -400.0f;
    const float TEXT_Y = 144.0f;
    const float XOFF = -32.0f;
    const float YOFF = -6.0f;
    const float SHADOW_X = 4;
    const float SHADOW_Y = 6;
    const float SHADOW_ALPHA = 0.5f;
    const float TEXT_SCALE = 0.75f;

    const float MENU_X = -128.0f;
    const float MENU_SCALE = 0.75f;
    const float MENY_YOFF_PLUS = 8.0f;

    const float ENTER_Y = 32.0f;
    const float ENTER_SCALE = 1.0f;
    
    const float COPYRIGHT_SCALE = 0.67f;
    const float COPYRIGHT_OFF = -8.0f;

    Vector2 view = g->getViewport();

    g->clearScreen(0.1f, 0.60f, 1.0f);

    // Set transform
    g->setView(VIEW_HEIGHT);
    g->identity();
    g->useTransf();

    float s = sinf(logoFloat) * LOGO_AMPLITUDE;
    float scale = logoScale*(LOGO_SCALE + cosf(logoFloat/2) * SCALE_MOD);
    float w = bmpLogo->getWidth() * scale;
    float h = bmpLogo->getHeight() * scale;


    // Draw shadow
    g->setColor(0, 0, 0, SHADOW_ALPHA);
    g->drawBitmap(bmpLogo, 
        view.x/2 - w/2 + LOGO_SHADOW_X,
        view.y/3 - h/2 +s + LOGO_SHADOW_Y,
        w, h);

    // Draw logo
    g->setColor();
    g->drawBitmap(bmpLogo, 
        view.x/2 - w/2,
        view.y/3 - h/2 +s,
        w, h);

    if(phase == 0) {

        // Draw copyright
        g->setColor(1, 1, 0);
        g->drawText(bmpFont, "(c)2019 Jani Nykanen", 
            view.x/2, 
            view.y-64*COPYRIGHT_SCALE+COPYRIGHT_OFF,
            XOFF, 0,
            SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
            COPYRIGHT_SCALE, true);

        // Draw "Press Enter"
        g->setColor(1, 1, 1,
            sinf(enterTimer)*0.5f+0.5f);
        g->drawText(bmpFont, "Press Enter", 
            view.x/2, 
            view.y/3*2 + ENTER_Y,
            XOFF, 0.0f, 
            SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
            ENTER_SCALE, true);
    }
    else {
        // Draw menu
        menu.draw(g, view.x/2+MENU_X, view.y/3.0f*2.0f, 
            MENU_SCALE, MENY_YOFF_PLUS);
    }
   
}


// Destroy scene
void Title::dispose() {
    
    // ...
}


// On change
void Title::onChange(void* param) {

    // ...
}   
