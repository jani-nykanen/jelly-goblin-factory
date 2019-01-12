// Game stage
// (c) 2019 Jani Nykänen

#ifndef __STAGE_H__
#define __STAGE_H__

#include "../../Core/Tilemap.hpp"
#include "../../Core/Graphics.hpp"
#include "../../Core/AssetPack.hpp"
#include "../../Core/EventManager.hpp"

#include "Communicator.hpp"

// View height
#define VIEW_HEIGHT 720.0f
// Constants
#define BASE_TILE_SIZE 128.0f

// Stage class
class Stage {

private:

    // Tilemap
    Tilemap* tmap;
    // Active data
    std::vector<int> data;
    // Solid data
    std::vector<int> solid;

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
    // Draw floor
    void drawFloor(Graphics *g);
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

    // Parse map for objects
    void parseMap(Communicator &comm);

    // Update
    void update(EventManager* evMan, float tm);
    // Draw
    void draw(Graphics* g, Communicator &comm);

    // Update solid data
    void updateSolid(int x, int y, int value);
    // Get solidity value of a tile
    int getSolidValue(int x, int y);

    // Get move target
    int getMoveTarget();
};


// Initialize global data
void initGlobalStage(AssetPack* assets);

#endif // __STAGE_H__
