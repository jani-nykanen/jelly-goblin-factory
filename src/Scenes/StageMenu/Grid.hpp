// Stage grid
// (c) 2019 Jani Nykänen

#ifndef __GRID_H__
#define __GRID_H__

#include "../../Core/Graphics.hpp"
#include "../../Core/EventManager.hpp"
#include "../../Core/AssetPack.hpp"

#include <cstdio>

typedef void (*GridCallback) (int);

// Block scale
struct BlockScale {

    float target;
    float scale;

    // Constructor
    inline BlockScale() {
        target = 1.0f;
        scale = 1.0f;
    }

    // Update
    void update(float tm);
};


// Grid class
class Grid {

private:

    // Bitmaps
    Bitmap* bmpFont;
    Bitmap* bmpBlocks;

    // Samples
    Sample* sSelect;
    Sample* sAccept;

    // Grid dimensions
    int width;
    int height;

    // Offset
    int xoff;
    int yoff;

    // Block dimensions
    Vector2 blockSize;
    // Block scales
    std::vector<BlockScale> blockScale;

    // Rendering info
    float rendw;
    float rendh;

    // Cursor position (in grid)
    Point cpos;
    // Cursor target (in grid)
    Point ctarget;
    // Cursor timer
    float ctimer;
    // Cursor float timer
    float cfloatTimer;
    // Cursor position ("virtual")
    Vector2 cvpos;
    // Page
    int page;

    // Reset scalings
    void resetBlockScalings();
    
    // Compute "virtual" cursor pos
    void computeCursorVpos();

    // Update cursor
    bool updateCursor(float tm);

public:

    // Constructors
    inline Grid(){};
    Grid(AssetPack* assets, int w, int h, 
        int blockw, int blockh, int xoff, int yoff);

    // Update
    void update(EventManager* evMan, GridCallback numberCb, float tm);
    // Draw
    void draw(Graphics* g, float tx=0, float ty=0, 
        std::vector<int>* completion=NULL);

    // Get chosen stage index
    int getChoseStageIndex();
    // Is the selected tile special
    bool isSpecialTile(int x, int y);
    bool isSpecialTile();

    // Set cursor position
    void setCursorPos(int i);
};

#endif // __GRID_H__
