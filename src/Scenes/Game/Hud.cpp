// HUD
// (c) 2019 Jani Nykänen

#include "Hud.hpp"

#include "../../Core/Utility.hpp"

#include <sstream>
#include <iostream>


// Constructor
Hud::Hud(AssetPack* assets) {

    // Get bitmaps
    bmpFont = assets->getBitmap("font");
}


// Update
void Hud::update() {

    // ...
}


// Draw
void Hud::draw(Graphics* g) {

    const float XOFF = -32;
    const float SHADOW_X = 4;
    const float SHADOW_Y = 6;
    const float SHADOW_ALPHA = 0.5f;
    const float SCALE = 1.0f;

    const float TEXT_X = 16;
    const float STAGE_Y = 16;
    const float TIME_Y = 72;
    const float STAR_Y = 72;

    // Draw stage text
    g->setColor();
    g->drawText(bmpFont, "Stage 1", TEXT_X, STAGE_Y, XOFF, 0,
        SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
    SCALE, false);

    // Draw time text
    std::string str;
    str.push_back((char)1);
    str += " :" + intToString(timer);
    g->drawText(bmpFont, str, TEXT_X, STAGE_Y+TIME_Y, XOFF, 0,
        SHADOW_X, SHADOW_Y, SHADOW_ALPHA,
    SCALE, false);

    // Draw star text
    str = "";
    str.push_back(timer <= turnTarget ? (char)2 : (char)3);
    str += " :" + intToString(turnTarget);
    g->drawText(bmpFont, str, TEXT_X, STAGE_Y+TIME_Y+STAR_Y, 
        XOFF, 0, SHADOW_X, SHADOW_Y, 
        SHADOW_ALPHA,
    SCALE, false);
}


// Reset
void Hud::reset() {

    timer = 0;
}
