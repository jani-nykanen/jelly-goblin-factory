// HUD
// (c) 2019 Jani Nykänen

#ifndef __HUD_H__
#define __HUD_H__

#include "../../Core/Graphics.hpp"
#include "../../Core/AssetPack.hpp"

// HUD
class Hud {

private:

    // Bitmaps
    Bitmap* bmpFont;

    // Info
    int time;
    int turnTarget;
    int stageID;

public:

    // Constructor
    inline Hud() {};
    Hud(AssetPack* assets);

    // Update
    void update();

    // Draw
    void draw(Graphics* g);

};

#endif // __HUD_H__
