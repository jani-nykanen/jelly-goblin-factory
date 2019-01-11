// Worker (or "game object")
// (c) 2019 Jani Nykänen

#ifndef __WORKER_H__
#define __WORKER_H__

#include "../../Core/Sprite.hpp"
#include "../../Core/Types.hpp"
#include "../../Core/AssetPack.hpp"
#include "../../Core/EventManager.hpp"

// Worker class
class Worker {

private:

    // Grid position
    Point pos;
    // Grid target
    Point target;
    // Virtual position
    Vector2 vpos;

    // Move timer
    float moveTimer;
    // Is moving
    bool moving;
    // Cog angle
    float angle;

    // Sprite
    Sprite spr;

    // Color
    int color;
    // Is sleeping
    bool sleeping;
    // Is cog
    bool isCog;

public:

    // Constructor
    inline Worker() {}
    Worker(Point p, int color, bool sleeping=false, bool isCog=false);

    // Update
    void update(EventManager* evMan, float tm);
    // Draw
    void draw(Graphics* g);
};

// Initialize global data
void initGlobalWorker(AssetPack* assets);

#endif //__WORKER_H__
