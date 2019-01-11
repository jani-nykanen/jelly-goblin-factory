// Worker (or "game object")
// (c) 2019 Jani Nykänen

#include "Worker.hpp"

#include "Stage.hpp"

// Bitmap
static Bitmap* bmpWorker;


// Initialize global data
void initGlobalWorker(AssetPack* assets) {

    // Get bitmaps
    bmpWorker = assets->getBitmap("worker");
}


// Constructor
Worker::Worker(Point p, int color, bool sleeping, bool isCog) {

    pos = p;
    vpos.x = p.x * BASE_TILE_SIZE;
    vpos.y = p.y * BASE_TILE_SIZE;

    this->color = color;
    this->sleeping = sleeping;
    this->isCog = isCog;

    angle = 0.0f;

    spr = Sprite(128, 128);
}


// Update
void Worker::update(EventManager* evMan, float tm) {

    const float STAND_SPEED = 8.0f;
    const float ROTATE_SPEED = 0.05f;

    if(isCog) {

        // Rotate
        angle += ROTATE_SPEED * tm;
    }
    else {

        // Animate sprite
        spr.animate(color, 0, 3, STAND_SPEED, tm);
    }
}


// Draw
void Worker::draw(Graphics* g) {

    const float COG_SCALE = 1.2f;

    if(isCog) {

        g->push();
        g->translate(vpos.x+BASE_TILE_SIZE/2, 
            vpos.y+BASE_TILE_SIZE/2);
        g->rotate(angle);
        g->scale(COG_SCALE, COG_SCALE);
        g->useTransf();

        // Draw cog
        spr.draw(g, bmpWorker, 7, 1, 
            -BASE_TILE_SIZE/2,
            -BASE_TILE_SIZE/2);

        g->pop();
        g->useTransf();

        // Draw eyes/face
        spr.draw(g, bmpWorker, 6, 1, vpos.x, vpos.y);

    }
    else {
        spr.draw(g, bmpWorker, vpos.x, vpos.y);
    }
}
