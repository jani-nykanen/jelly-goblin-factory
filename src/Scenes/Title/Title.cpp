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
    sAccept = assets->getSample("accept");
    sSelect = assets->getSample("select");

    // Create menu
    std::vector<MenuButton> buttons;
    buttons.push_back(MenuButton("Play", cb_Play, true, 2.0f));
    buttons.push_back(MenuButton("Settings", NULL));
    buttons.push_back(MenuButton("Clear Data", NULL));
    buttons.push_back(MenuButton("Quit", cb_Terminate, true, 2.0f));
    menu = Menu(buttons);

    // Set defaults
    logoFloat = 0.0f;
}


// Update scene
void Title::update(float tm) {

    const float LOGO_FLOAT = 0.05f;

    if(trans->isActive()) return;

    GamePad* vpad = evMan->getController();
    AudioManager* audio = evMan->getAudioManager();

    // Update logo float
    logoFloat += LOGO_FLOAT * tm;
    logoFloat = fmodf(logoFloat, M_PI*4.0f);

    // Update menu
    menu.update(evMan);
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

    Vector2 view = g->getViewport();

    g->clearScreen(0.1f, 0.60f, 1.0f);

    // Set transform
    g->setView(VIEW_HEIGHT);
    g->identity();
    g->useTransf();

    float s = sinf(logoFloat) * LOGO_AMPLITUDE;
    float scale = LOGO_SCALE + cosf(logoFloat/2) * SCALE_MOD;
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

    // Draw menu
    menu.draw(g, view.x/2+MENU_X, view.y/3.0f*2.0f, 
        MENU_SCALE, MENY_YOFF_PLUS);
   
}


// Destroy scene
void Title::dispose() {
    
    // ...
}


// On change
void Title::onChange(void* param) {

    // ...
}   
