// Title screen scene
// (c) 2019 Jani Nykänen

#include "Title.hpp"

#include "../Game/Stage.hpp"

#include "../../Core/SceneManager.hpp"
#include "../../version.hpp"

// Reference to self
static Title* tref;

// Callbacks
static void cb_Play() {
    tref->goToStageMenu();
}
static void cb_Settings() {
    tref->activateSettings();
}
static void cb_Confirm() {
    tref->activateConfirmMenu();
}
static void cb_Terminate() {
    tref->terminate();
}
static void cb_SFX() {tref->toggleSFX();}
static void cb_Music() {tref->toggleMusic();}
static void cb_Fullscreen() {tref->toggleFullscreen();}
static void cb_Back() {tref->disableSettings();}

static void cb_ClearData() { tref->removeData(); }
static void cb_Reject() { tref->disableConfirmMenu(); }



// Draw a cog
void Title::drawCog(Graphics* g, float x, float y,
    float scale, int dir) {

    g->push();
    g->translate(x, y);
    g->rotate(cogAngle * dir);
    g->scale(scale, scale);
    g->useTransf();

    g->drawBitmap(bmpCog, -128, -128);

    g->pop();
}


// Draw cogs
void Title::drawCogs(Graphics* g) {

    const float SCALE = 1.25f;
    const float SHADOW_ALPHA = 0.5f;
    const float SHADOW_X = 12.0f;
    const float SHADOW_Y = 12.0f;

    Vector2 view = g->getViewport();

    // Draw one cog to every corner
    g->setColor();
    for(int y = 0; y < 2; ++ y) {
        
        for(int x = 0; x < 2; ++ x) {

            // Shadow
            g->setColor(0, 0, 0, SHADOW_ALPHA);
            drawCog(g, 
                x*view.x + SHADOW_X, 
                y*view.y + SHADOW_Y, 
                SCALE, 
                x == 0 ? -1 : 1);

            // Base cog
            g->setColor();
            drawCog(g, x*view.x, y*view.y, SCALE, x == 0 ? -1 : 1);
        }

    }
    g->useTransf();
}


// Go to the stage menu
void Title::goToStageMenu() {

    void* pp = NULL;
    Point p = Point(0, 0);
    if(dataRemoved) {

        p.x = -1;
        p.y = -1;
        pp = (void*)&p;
        dataRemoved = false;
    }

    sceneMan->changeActiveScene("stageMenu", pp);
}


// Toggle SFX
void Title::toggleSFX() {

    AudioManager* audio = evMan->getAudioManager();
    audio->toggleSfx();

    std::string text = "SFX: " + 
        (audio->isSfxEnabled() ? std::string("On") : std::string("Off"));

    settings.setButtonText(0, text);
}


// Toggle music
void Title::toggleMusic() {

    AudioManager* audio = evMan->getAudioManager();
    audio->toggleMusic();

    std::string text = "Music: " + 
        (audio->isMusicEnabled() ? std::string("On") : std::string("Off"));

    settings.setButtonText(1, text);
}


// Activate settings
void Title::activateSettings() {

    AudioManager* audio = evMan->getAudioManager();
    // Set text
    std::string text = "SFX: " + 
        (audio->isSfxEnabled() ? std::string("On") : std::string("Off"));
    settings.setButtonText(0, text);
    text = "Music: " + 
        (audio->isMusicEnabled() ? std::string("On") : std::string("Off"));
    settings.setButtonText(1, text);

    settings.activate(3);
}


// Remove data
void Title::removeData() {

    remove("save.dat");
    dataRemoved = true;

    confirmMenu.deactivate();
}


// Activate confirm menu
void Title::activateConfirmMenu() {

    confirmMenu.activate(1);
}


// Initialize scene
void Title::init() {
    
    // TODO: Get these from one place, now
    // they are the same as in "Game"
    const float SETTINGS_WIDTH = 400.0f;
    const float SETTINGS_HEIGHT = 288.0f;
    const float SETTINGS_SCALE = 1.0f;

    const float CONFIRM_WIDTH = 256.0f;
    const float CONFIRM_HEIGHT = 144.0f;

    tref = this;

    // Get "global" objects
    trans = evMan->getTransition();

    // Get bitmaps
    bmpFont = assets->getBitmap("font");
    bmpLogo = assets->getBitmap("logo");
    bmpCog = assets->getBitmap("cog");
    // Get samples
    sPause = assets->getSample("pause");
    sReject = assets->getSample("reject");
    // Get music
    mMenu = assets->getMusic("menu");

    // Create menu
    std::vector<MenuButton> buttons;
    buttons.push_back(MenuButton("Play", cb_Play, true, 2.0f));
    buttons.push_back(MenuButton("Settings", cb_Settings));
    buttons.push_back(MenuButton("Clear Data", cb_Confirm));
    buttons.push_back(MenuButton("Quit", cb_Terminate, true, 2.0f));
    menu = Menu(buttons);

    // Create settings
    buttons.clear();
    buttons.push_back(MenuButton("SFX: On", cb_SFX));
    buttons.push_back(MenuButton("Music: On", cb_Music));
    buttons.push_back(MenuButton("Fullscreen", cb_Fullscreen));
    buttons.push_back(MenuButton("Back", cb_Back));
    settings = PauseMenu(buttons, 
        SETTINGS_WIDTH, SETTINGS_HEIGHT, 
        SETTINGS_SCALE);

    // Create confirm menu
    buttons.clear();
    buttons.push_back(MenuButton("Yes", cb_ClearData));
    buttons.push_back(MenuButton("No", cb_Reject));
    confirmMenu = PauseMenu(buttons, 
        CONFIRM_WIDTH, CONFIRM_HEIGHT, 
        SETTINGS_SCALE);

    // Set defaults
    logoFloat = 0.0f;
    logoScale = 0.0f;
    phase = 0;
    enterTimer = -M_PI/2.0f;
    logoStopped = false;
    dataRemoved = false;
    cogAngle = 0.0f;
}


// Update scene
void Title::update(float tm) {

    const float LOGO_FLOAT = 0.05f;
    const float ENTER_TIMER_SPEED = 0.05f;
    const float COG_SPEED = 0.05f;

    // Check settings
    if(settings.isActive()) {

        settings.update(evMan, true);
        return;
    }

    // Check confirm menu
    if(confirmMenu.isActive()) {

        confirmMenu.update(evMan, true);
        return;
    }

    // Update logo scale using
    // transition object
    float t = 1.0f-trans->getTime();
    if(logoScale < t) {

        logoScale = t;
    }

    // Update cog angle
    cogAngle += COG_SPEED * tm;
    cogAngle = fmodf(cogAngle, M_PI*2);

    if(trans->isActive()) return;

    GamePad* vpad = evMan->getController();
    AudioManager* audio = evMan->getAudioManager();

    // Update logo float
    if(!logoStopped) {
        float oldFloat = logoFloat;
        logoFloat += LOGO_FLOAT * (phase*2+1) * tm;
        if(phase == 1 && (
            (oldFloat < M_PI*2.0f && logoFloat >= M_PI*2.0f) || 
            (logoFloat >= M_PI*4.0f)
            )) {
            
            logoFloat = 0.0f;
            logoStopped = true;
        }
        logoFloat = fmodf(logoFloat, M_PI*4.0f);
    }

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

    const float CONFIRM_SCALE = 1.25f;
    const float CONFIRM_MENU_Y = 64.0f;

    const float VERSION_SCALE = 0.5f;

    Vector2 view = g->getViewport();

    g->clearScreen(0.1f, 0.60f, 1.0f);

    // Set transform
    g->setView(VIEW_HEIGHT);
    g->identity();
    g->useTransf();

    // Draw cogs
    drawCogs(g);

    float s = sinf(logoFloat) * LOGO_AMPLITUDE;
    float scale = logoScale*(LOGO_SCALE + sinf(logoFloat/2) * SCALE_MOD);
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
        g->drawText(bmpFont, "(c)2019 Jani Nyk~nen", 
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

        // Draw settings
        settings.draw(g);

        // Draw confirm menu
        if(confirmMenu.isActive()) {

            // Draw menu
            confirmMenu.draw(g, 0, CONFIRM_MENU_Y);

            // Draw title
            g->setColor(1, 0.25f, 0.25f);
            g->drawText(bmpFont, "Are you sure?", 
                view.x/2, 
                view.y/3, 
                XOFF, 0, 
                SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
                CONFIRM_SCALE, true);
        }
    }

    // Draw version
    g->setColor();
    std::string vstr = "v."+ std::string(VERSION_NUMBER);
    g->drawText(bmpFont, vstr, 
        view.x-(vstr.length()+1)*( (64+XOFF)*VERSION_SCALE),
        view.y-VERSION_SCALE*64.0f, XOFF, 0,
        VERSION_SCALE, false);
   
}


// Destroy scene
void Title::dispose() {
    
    // ...
}


// On change
void Title::onChange(void* param) {

    if(param == NULL)
        return;

    // Start music
    if((int)(size_t)param == 1) {

        AudioManager* audio = evMan->getAudioManager();
        audio->fadeInMusic(mMenu, MENU_MUSIC_VOL, 1000);
    }
}   
