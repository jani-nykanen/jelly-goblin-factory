// Game stage
// (c) 2019 Jani Nykänen

#ifndef __STAGE_H__
#define __STAGE_H__

#include "../../Core/Tilemap.hpp"
#include "../../Core/Graphics.hpp"
#include "../../Core/AssetPack.hpp"
#include "../../Core/EventManager.hpp"

// View height
#define VIEW_HEIGHT 720.0f

// Stage class
class Stage {

private:

    // Tilemap
    Tilemap* tmap;
    // Active data
    std::vector<int> data;

    // Dimensions (in tiles)
    int width;
    int height;

    // Stage scale & sizes
    float scale;
    float scaledWidth;
    float scaledHeight;
    float baseWidth;
    float baseHeight;

    // Cog angle
    float cogAngle;

    // Get a tile
    int getTile(int x, int y);

    // Draw walls
    void drawWalls(Graphics* g);
    // Draw borders
    void drawBorders(Graphics* g);
    // Draw shadow
    void drawShadow(Graphics* g);

    // Draw a single cog
    void drawCog(Graphics* g, float x, float y, 
        float scale, float angle);
    // Draw background cogs
    void drawCogs(Graphics* g);

public:

    // Constructor
    Stage(std::string mapPath);
    // Desctructor
    ~Stage();

    // Update
    void update(EventManager* evMan, float tm);
    // Draw
    void draw(Graphics* g);
};


// Initialize global data
void initGlobalStage(AssetPack* assets);

#endif // __STAGE_H__
