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
    int timer;
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

    // Set info
    inline void addMove() {
        ++ timer;
    }
    inline void setMoveTarget(int t) {
        turnTarget = t;
    }

    // Getters
    inline bool isPerfectClear() {

        return timer <= turnTarget;
    }

    // Reset
    void reset();

};

#endif // __HUD_H__
