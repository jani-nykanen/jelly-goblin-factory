// Stage menu scene
// (c) 2019 Jani Nykänen

#ifndef __STAGE_MENU_H__
#define __STAGE_MENU_H__

#include "../../Core/Scene.hpp"
#include "../../Core/Bitmap.hpp"

#include "../Game/Stage.hpp"

#include "Grid.hpp"

// Stage menu class
class StageMenu : public Scene {

private:

    // Bitmaps
    Bitmap* bmpFont;

    // Grid
    Grid stageGrid;

public: 

    // Initialize scene
    void init();
    // Update scene
    void update(float tm);
    // Draw scene
    void draw(Graphics* g);
    // Dispose scene
    void dispose();
    // Called when the scene is changed
    // to this scene
    void onChange();

    // Get name
    inline std::string getName() {

        return "stageMenu";
    }
};

#endif // __STAGE_MENU_H__
