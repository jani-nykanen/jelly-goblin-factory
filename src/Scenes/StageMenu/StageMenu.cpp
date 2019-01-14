// Stage menu scene
// (c) 2019 Jani Nykänen

#include  "StageMenu.hpp"


// Initialize scene
void StageMenu::init() {

    const int WIDTH = 6;
    const int HEIGHT = 4;
    const float BUTTON_W = 92;
    const float BUTTON_H = 92;
    const float XOFF = 20;
    const float YOFF = 20;

    // Get bitmaps
    bmpFont = assets->getBitmap("font");

    // Create components
    stageGrid = Grid(assets, WIDTH, HEIGHT, 
        BUTTON_W, BUTTON_H, XOFF, YOFF);
}


// Update scene
void StageMenu::update(float tm) {

    // Update grid
    stageGrid.update(evMan, tm);
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
    g->drawText(bmpFont, "Choose a stage", 
        view.x/2, HEADER_Y, XOFF, 0,
        SHADOW_X, SHADOW_Y, SHADOW_ALPHA, 
        HEADER_SCALE, true);

    // Draw grid
    stageGrid.draw(g, 0, GRID_YOFF);
}


// Dispose scene
void StageMenu::dispose() {

}


// Called when the scene is changed
// to this scene
void StageMenu::onChange() {

}
