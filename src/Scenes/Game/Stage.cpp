// Game stage
// (c) 2019 Jani Nykänen

#include "Stage.hpp"

// Constants
static const float BASE_TILE_SIZE = 128.0f;

// Bitmaps
static Bitmap* bmpWall;
static Bitmap* bmpBorders;


// Initialize global data
void initGlobalStage(AssetPack* assets) {

    // Get assets
    bmpWall = assets->getBitmap("wall");
    bmpBorders = assets->getBitmap("borders");
}


// Draw walls
void Stage::drawWalls(Graphics* g) {

    int x, y;
    for(int i = 0; i < width*height; ++ i) {

        if(data[i] != 1) 
            continue;;

        x = i % width;
        y = i / width;

        g->drawBitmap(bmpWall, x*BASE_TILE_SIZE, 
            y*BASE_TILE_SIZE);
    }
}


// Draw borders
void Stage::drawBorders(Graphics *g) {

    const float borderSize = bmpBorders->getWidth() / 3;

    // Draw corners
    for(int x = 0; x <= 1; ++ x) {
        for(int y = 0; y <= 1; ++ y) {

            g->drawBitmap(bmpBorders, 0, 0, borderSize, borderSize,
                -borderSize + (baseWidth+borderSize)*x, 
                -borderSize + (baseHeight+borderSize)*y);
        }
    }

    // Draw horizontal
    g->drawBitmap(bmpBorders, borderSize+1, 0, 
                borderSize-2, borderSize,
                0, -borderSize, baseWidth, borderSize);
    g->drawBitmap(bmpBorders, borderSize+1, borderSize*2, 
                borderSize-2, borderSize,
                0, baseHeight, baseWidth, borderSize);

    // Draw vertical
    g->drawBitmap(bmpBorders, 0, borderSize+1, 
                borderSize, borderSize-2,
                -borderSize, 0, borderSize, baseHeight);
    g->drawBitmap(bmpBorders, borderSize*2, borderSize+1, 
                borderSize, borderSize-2,
                baseWidth, 0, borderSize, baseHeight);
}


// Draw shadow
void Stage::drawShadow(Graphics* g) {

    const float SHADOW_OFF = 32.0f;
    const float borderSize = bmpBorders->getWidth() / 3;

    g->setColor(0, 0, 0, 0.5f);
    g->fillRect(-borderSize + SHADOW_OFF, 
                -borderSize+SHADOW_OFF,
                baseWidth+borderSize*2, 
                baseHeight+borderSize*2);
}


// Constructor
Stage::Stage(std::string mapPath) {

    // Load tilemap
    tmap = new Tilemap(mapPath);

    // Get information
    data = tmap->copyData();
    width = tmap->getWidth();
    height = tmap->getHeight();

    // Compute scale
    baseWidth = width * BASE_TILE_SIZE;
    baseHeight = height * BASE_TILE_SIZE;
    scale = 1.0f / ( ((height+2)*BASE_TILE_SIZE) / VIEW_HEIGHT );
    scaledWidth = scale * baseWidth;
    scaledHeight = scale * baseHeight;
}
// Desctructor
Stage::~Stage() {

    delete tmap;
}


// Update
void Stage::update(EventManager* evMan, float tm) {

}


// Draw
void Stage::draw(Graphics* g) {

    // Get viewport
    Vector2 view = g->getViewport();

    // Set view
    g->push();
    g->translate(view.x/2, view.y/2);
    g->scale(scale, scale);
    g->translate(-baseWidth/2, -baseHeight/2);
    g->useTransf();

    // Draw shadow
    drawShadow(g);

    // Clear to black
    g->setColor(0, 0, 0);
    g->fillRect(0, 0, baseWidth, baseHeight);

    // Draw walls
    g->setColor();
    drawWalls(g);

    // Draw borders
    drawBorders(g);

    g->pop();
    g->useTransf();
}
