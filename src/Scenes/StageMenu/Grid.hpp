// Stage grid
// (c) 2019 Jani Nykänen

#ifndef __GRID_H__
#define __GRID_H__

#include "../../Core/Graphics.hpp"
#include "../../Core/EventManager.hpp"
#include "../../Core/AssetPack.hpp"


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

    // Cursor position
    Point cpos;

public:

    // Constructors
    inline Grid(){};
    Grid(AssetPack* assets, int w, int h, 
        int blockw, int blockh, int xoff, int yoff);

    // Update
    void update(EventManager* evMan, float tm);
    // Draw
    void draw(Graphics* g, float tx=0, float ty=0);
};

#endif // __GRID_H__
