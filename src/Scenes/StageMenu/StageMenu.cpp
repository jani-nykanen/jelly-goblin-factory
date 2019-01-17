// Stage menu scene
// (c) 2019 Jani Nykänen

#include  "StageMenu.hpp"

#include "../../Core/Utility.hpp"
#include "../../Core/SceneManager.hpp"

// Reference to self
static StageMenu* smRef;


// Get difficulty string
static std::string getDifficultyString(int level) {

    std::string ret = "";
    int i = 0;
    for(; i < level/2; ++ i) {

        ret += (char)7;
    }
    if(level % 2 != 0)
        ret += (char)8;

    return ret;
}


// Callbacks
static void cb_GoToStage() {
    smRef->goToStage();
}
static void cb_NumButton(int b) {

    smRef->setStageTarget(b);
    smRef->fadeToTarget(cb_GoToStage);
}


// Draw stage info
void StageMenu::drawStageInfo(Graphics* g) {

    const float XOFF = -32.0f;
    const float HEADER_Y = 128.0f;
    const float INFO_Y = 80.0f;
    const float HEADER_SCALE = 0.625f;
    const float BASE_SCALE = 0.80f;
    const float SHADOW_X = 4.0f;
    const float SHADOW_Y = 6.0f;
    const float SHADOW_ALPHA = 0.5f;
    const float DIFF_OFF = -128.0f;

    // Check if the stage in the cursor
    // position exists
    int index = stageGrid.getChoseStageIndex() -1;
    if(index < 0 || index >= maps.size()) {
        return;
    }

    Vector2 view = g->getViewport();

    // Headers
    g->setColor();
    g->drawText(bmpFont, "Stage name:", 
        view.x/2 - view.x/4, view.y-HEADER_Y, 
        XOFF, 0, SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
        HEADER_SCALE, true);

    g->drawText(bmpFont, "Difficulty:", 
        view.x/2 + view.x/4, view.y-HEADER_Y, 
        XOFF, 0, SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
        HEADER_SCALE, true);

    // Info
    g->setColor(1, 1, 0);
    g->drawText(bmpFont,"\"" + mapNames[index] + "\"", 
        view.x/2 - view.x/4, view.y-INFO_Y, 
        XOFF, 0, SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
        BASE_SCALE, true);

    g->setColor();
    g->drawText(bmpFont, getDifficultyString(mapDiff[index]), 
        view.x/2 + view.x/4 + DIFF_OFF, view.y-INFO_Y, 
        0, 0, SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
        BASE_SCALE, false);
}


// Go to the selected stage
void StageMenu::goToStage() {

    if(stageTarget <= 0 || stageTarget > maps.size()) {

        printf("Stage not implemented yet.\n");
        return;
    }
    
    StageInfo sinfo;
    sinfo.tmap = &maps[stageTarget-1];
    sinfo.stageIndex = stageTarget;

    sceneMan->changeActiveScene("game", (void*)&sinfo);
}


// Fade to something
void StageMenu::fadeToTarget(TransitionCallback cb) {

    trans->activate(FadeIn, 2.0f, cb);
}


// Initialize scene
void StageMenu::init() {

    const int WIDTH = 6;
    const int HEIGHT = 4;
    const float BUTTON_W = 92;
    const float BUTTON_H = 92;
    const float XOFF = 20;
    const float YOFF = 20;

    smRef = this;

    // Get "global" objects
    trans = evMan->getTransition();

    // Get bitmaps
    bmpFont = assets->getBitmap("font");

    // Create components
    stageGrid = Grid(assets, WIDTH, HEIGHT, 
        BUTTON_W, BUTTON_H, XOFF, YOFF);

    // Find existing maps & load them
    const std::string BASE_PATH = "Assets/Tilemaps/New/";
    const int MAX = 100;
    maps = std::vector<Tilemap> ();
    mapNames = std::vector<std::string> ();
    mapDiff = std::vector<int> ();
    try {

        for(int i = 1; i <= MAX; ++ i) {

            maps.push_back(Tilemap(BASE_PATH 
                + intToString(i) + ".tmx"));

            // Get info
            mapNames.push_back(maps[i-1].getProp("name"));
            mapDiff.push_back(strToInt(maps[i-1].getProp("difficulty")));
        }
    }
    catch(std::exception e){}
}


// Update scene
void StageMenu::update(float tm) {

    if(trans->isActive()) return;

    // Update grid
    stageGrid.update(evMan, cb_NumButton, tm);
}


// Draw scene
void StageMenu::draw(Graphics* g) {

    const float XOFF = -32.0f;
    const float HEADER_Y = 32.0f;
    const float HEADER_SCALE = 1.0f;
    const float SHADOW_X = 4.0f;
    const float SHADOW_Y = 6.0f;
    const float SHADOW_ALPHA = 0.5f;
    const float GRID_YOFF = -16.0f;

    Vector2 view = g->getViewport();

    g->clearScreen(0.1f, 0.60f, 1.0f);

    // Set transform
    g->setView(VIEW_HEIGHT);
    g->identity();
    g->useTransf();

    // Draw header
    g->setColor();
    g->drawText(bmpFont, "Choose a stage", 
        view.x/2, HEADER_Y, XOFF, 0,
        SHADOW_X, SHADOW_Y, SHADOW_ALPHA, 
        HEADER_SCALE, true);

    // Draw grid
    stageGrid.draw(g, 0, GRID_YOFF);

    if(!stageGrid.isSpecialTile()) {

        // Draw stage info
        drawStageInfo(g);
    }
}


// Dispose scene
void StageMenu::dispose() {

}


// Called when the scene is changed
// to this scene
void StageMenu::onChange(void* param) {

    int v = (int)(size_t)param;

    if(v == 1 && stageTarget < maps.size()) {

        ++ stageTarget;
        stageGrid.setCursorPos(stageTarget);
        goToStage();
    }
}
