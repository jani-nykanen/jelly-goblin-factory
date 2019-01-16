// Worker (or "game object")
// (c) 2019 Jani Nykänen

#ifndef __WORKER_H__
#define __WORKER_H__

#include "../../Core/Sprite.hpp"
#include "../../Core/Types.hpp"
#include "../../Core/AssetPack.hpp"
#include "../../Core/EventManager.hpp"

#include "Stage.hpp"

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
    // Has stopped
    bool stopped;
    // Has started moving
    bool startedMoving;

    // Is transforming
    bool transforming;
    // Transform timer
    float transfTimer;

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

    // Find a free tile
    bool findFreeTile(int dx, int dy, Stage* stage);
    // Control
    void control(EventManager* evMan, Stage* stage, bool anyMoving);
    // Move
    void move(Stage* stage, float tm);
    // Animate
    void animate(float tm);
    
    // Transform
    void transform(float tm);

    // Check nearby tile (for cog!)
    bool checkNearbyTile(Stage* stage, int color);

public:

    // Constructor
    inline Worker() {}
    Worker(Point p, int color, bool sleeping=false, bool isCog=false);

    // Update
    void update(EventManager* evMan, Stage* stage,  
        bool anyMoving, float tm);
    // Draw
    void draw(Graphics* g);

    // Check cog collision
    void checkCogCollision(Stage* stage);

    // Getters
    inline bool isMoving() {

        return moving;
    }
    inline bool hasStartedMoving() {

        return startedMoving;
    }
    inline bool isActive() {

        return transforming || moving;
    }
    // A little misleading, yes
    inline bool isAlive() {

        return !isCog && color >= 0;
    }
};

// Initialize global data
void initGlobalWorker(AssetPack* assets);

#endif //__WORKER_H__
