// Worker (or "game object")
// (c) 2019 Jani Nykänen

#include "Worker.hpp"

#include "Stage.hpp"

#include <cmath>
#include <cstdlib>
#include <stdio.h>

// Constants
static const float MOVE_TIME = 20;
static const float TRANSFORM_TIME = 20;

// Bitmap
static Bitmap* bmpWorker;


// Initialize global data
void initGlobalWorker(AssetPack* assets) {

    // Get bitmaps
    bmpWorker = assets->getBitmap("worker");
}


// Find a free tile
bool Worker::findFreeTile(int dx, int dy, Stage* stage) {

    int x = pos.x;
    int y = pos.y;
    int tileID;

    // Check if there is an empty tile
    // in the given direction
    while(true) {

        x += dx;
        y += dy;

        tileID = stage->getSolidValue(x, y);
        if(tileID == 0) {

            return true;
        }
        else if(tileID == 1 || tileID >= 3) {

            break;
        }
    }
    return false;
}


// Control
void Worker::control(EventManager* evMan, 
    Stage* stage, bool anyMoving) {

    const float DELTA = 0.25f;

    // Check controls only if something is
    // not happening (or if something that
    // should not move in the first place)
    if(sleeping || isCog || moving || anyMoving)
        return;

    // Check move direction
    int dx = 0;
    int dy = 0;
    Vector2 stick = evMan->getController()->getStick();
    
    // Check stick distance
    float dist = hypotf(stick.x, stick.y);
    if(dist < DELTA) {

        return;
    }

    // Check angle
    float angle = atan2f(stick.y, stick.x);
    float quarter = M_PI / 4.0f;
    float full = M_PI *2.0f;
    // Right
    if(angle < quarter && angle >= -quarter) 
        dx = 1;
    // Up
    else if(angle < -quarter && angle >= -M_PI+quarter)
        dy = -1;
    // Down
    else if(angle >= quarter && angle < M_PI-quarter)
        dy = 1;
    // Left
    else
        dx = -1;


    // Set destination
    target.x = pos.x+dx;
    target.y = pos.y+dy;

    // Check if free
    if(!findFreeTile(dx, dy, stage)) {

        target.x = pos.x;
        target.y = pos.y;

        return;
    }

    // Start moving
    moving = true;
    moveTimer = MOVE_TIME;
    startedMoving = true;

    // Update solid data
    stage->updateSolid(pos.x, pos.y, 0);
}


// Move
void Worker::move(Stage* stage, float tm) {

    // Ignore inactive workers
    if(isCog || sleeping) return;

    // Update virtual position
    if(!moving) {

        vpos.x = pos.x * BASE_TILE_SIZE;
        vpos.y = pos.y * BASE_TILE_SIZE;
        return;
    }

    // Compute virtual position
    float t = moveTimer / MOVE_TIME;
	vpos.x = (pos.x*BASE_TILE_SIZE)*t 
        + (1-t)*(target.x*BASE_TILE_SIZE);
	vpos.y = (pos.y*BASE_TILE_SIZE)*t 
        + (1-t)*(target.y*BASE_TILE_SIZE);

    // Update move timer
    if( (moveTimer -= 1.0f* tm) <= 0.0f) {

        moveTimer = 0.0f;
        moving = false;

        pos.x = target.x;
        pos.y = target.y;

        // Update solid
        stage->updateSolid(pos.x, pos.y, 2);
    }
}


// Animate
void Worker::animate(float tm) {

    const float STAND_SPEED = 8.0f;
    const float WALK_SPEED = 6.0f;
    const float SLEEP_SPEED = 60.0f;
    const float ROTATE_SPEED = 0.05f;

    if(isCog) {

        int dir = ((pos.y % 2 == 0 && pos.x % 2 == 0) ||
                (pos.y % 2 == 1 && pos.x % 2 == 1))
                ? 1 : -1;

        // Rotate
        angle += ROTATE_SPEED * tm * dir;
    }
    else {

        // Sleeping
        if(sleeping) {

            spr.animate(color*2+1, 0, 1, SLEEP_SPEED, tm);
        }
        // Awake
        else {

            bool cond = (moving);
            int frameSkip = cond ? 4 : 0;

            // Animate sprite
            spr.animate(color*2, frameSkip, frameSkip+3, 
                cond ? WALK_SPEED : STAND_SPEED, tm);
        }
    }
}


// Transform
void Worker::transform(float tm) {

    const float ANIM_SPEED = 3.0f;

    // Animate
    if(spr.getFrame() != 5 || spr.getRow() != color*2+1)
        spr.animate(color*2+1, 2, 5, ANIM_SPEED, tm);

    // Update timer
    transfTimer -= 1.0f *tm;
    if(transfTimer <= 0.0f) {

        transforming = false;
    }
}


// Check cog collision
void Worker::checkCogCollision(Stage* stage) {

    if(moving || isCog)
        return;

    // Check nearby tiles
    if(stage->getSolidValue(pos.x,pos.y-1) == 3+color
    || stage->getSolidValue(pos.x,pos.y+1) == 3+color
    || stage->getSolidValue(pos.x-1,pos.y) == 3+color
    || stage->getSolidValue(pos.x+1,pos.y) == 3+color) {

        isCog = true;
        moving = false;
        transforming = true;
        transfTimer = TRANSFORM_TIME;

        stage->updateSolid(pos.x, pos.y, 3+color);
    }

}

// Constructor
Worker::Worker(Point p, int color, bool sleeping, bool isCog) {

    // Set pos
    pos = p;
    vpos.x = p.x * BASE_TILE_SIZE;
    vpos.y = p.y * BASE_TILE_SIZE;

    // Set params
    this->color = color;
    this->sleeping = sleeping;
    this->isCog = isCog;
    angle = 0.0f;

    // Set defaults
    moving = false;
    moveTimer = 0.0f;
    startedMoving = false;
    transforming = false;
    transfTimer = 0.0f;

    // Create sprite
    spr = Sprite(128, 128);
    // Set beginning frame
    startRow = color*2;
    int frame = 0;
    if(!sleeping) {

        frame = rand() % 4;
    }
    else {

        frame = rand() % 2;
        ++ startRow;
    }
    spr.setFrame(startRow, frame);
}


// Update
void Worker::update(EventManager* evMan, Stage* stage, 
    bool anyMoving,  float tm) {

    startedMoving = false;

    // Transform
    if(isCog && transforming) {

        transform(tm);
    }

    // Control
    control(evMan, stage, anyMoving);
    // Move
    move(stage, tm);
    // Animate
    animate(tm);
}


// Draw
void Worker::draw(Graphics* g) {

    const float COG_SCALE = 1.2f;
    const float TRANSF_SCALE = 1.5f;
    const int TRANSF_FRAMES = 3;

    if(isCog) {

        float t = transforming ? transfTimer / TRANSFORM_TIME : 0.0f;

        g->push();
        g->translate(vpos.x+BASE_TILE_SIZE/2, 
            vpos.y+BASE_TILE_SIZE/2);
        g->rotate(angle);
        g->scale(COG_SCALE*(1-t), COG_SCALE*(1-t));
        g->useTransf();

        // Draw cog
        spr.draw(g, bmpWorker, 7, color*2+1, 
            -BASE_TILE_SIZE/2,
            -BASE_TILE_SIZE/2);

        g->pop();
        g->useTransf();

        // Draw transforming sprite
        if(transforming) {

            float s = 1.0f + (1.0f-t) * (TRANSF_SCALE-1.0f);

            g->push();
            g->translate(vpos.x+BASE_TILE_SIZE/2, 
                vpos.y+BASE_TILE_SIZE/2);
            g->scale(s, s);
            g->useTransf();

            g->setColor(1,1,1, t);
            spr.draw(g, bmpWorker,
                -BASE_TILE_SIZE/2,
                -BASE_TILE_SIZE/2);
            g->setColor();

            g->pop();
            g->useTransf();
            
        }

        // Draw eyes/face
        spr.draw(g, bmpWorker, 6, color*2+1, vpos.x, vpos.y);

    }
    else {
        spr.draw(g, bmpWorker, vpos.x, vpos.y);
    }
}
