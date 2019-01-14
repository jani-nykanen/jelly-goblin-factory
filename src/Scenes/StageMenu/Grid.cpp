// Stage grid
// (c) 2019 Jani Nykänen

#include "Grid.hpp"

#include "../../Core/Utility.hpp"


// Update block size
void BlockScale::update(float tm) {

    const float SPEED = 0.025f;

    if(scale < target) {

        scale += SPEED * tm;
        if(scale >= target)
            scale = target;
    }
    else if(scale > target) {

        scale -= SPEED * tm;
        if(scale <= target)
            scale = target;
    }
}


// Constructor
Grid::Grid(AssetPack* assets, int w, int h, 
        int blockw, int blockh, int xoff, int yoff) {

    // Get bitmaps
    bmpFont = assets->getBitmap("font");
    bmpBlocks = assets->getBitmap("blocks");

    // Store info
    width = w;
    height = h;
    this->xoff = xoff;
    this->yoff = yoff;
    blockSize = Vector2(blockw, blockh);

    // Compute rendering info
    rendw = (blockSize.x + xoff) * width;
    rendh = (blockSize.y + yoff) * height;

    // Set defaults
    cpos.x = 0;
    cpos.y = 0;

    // Set block scales to default
    blockScale = std::vector<BlockScale> (width*height);
    for(int i = 0; i < width*height; ++ i) {

        blockScale[i] = BlockScale();
        blockScale[i].scale = blockSize.x/128.0f;
        blockScale[i].target = blockScale[i].scale;
    }
}


// Update
void Grid::update(EventManager* evMan, float tm) {

    const float DELTA = 0.25f;

    GamePad* vpad = evMan->getController();
    Vector2 stick = vpad->getStick();
    Vector2 delta = vpad->getDelta();

    // Update cursor position
    if(stick.x < -DELTA && delta.x < -DELTA) {

        if(-- cpos.x < 0)
            cpos.x += width;
    }
    else if(stick.x > DELTA && delta.x > DELTA) {

        if(++ cpos.x >= width)
            cpos.x -= width;
    }
    if(stick.y < -DELTA && delta.y < -DELTA) {

        if(-- cpos.y < 0)
            cpos.y += height;
    }
    else if(stick.y > DELTA && delta.y > DELTA) {

        if(++ cpos.y >= height)
            cpos.y -= height;
    }

    // Update block scales
    for(int i = 0; i < blockScale.size(); ++ i) {

        blockScale[i].update(tm);
    }
}


// Draw
void Grid::draw(Graphics* g, float tx, float ty) {

    const float DARKEN = 0.80f;
    const float TEXT_XOFF = -32.0f;
    const float TEXT_BASE_SCALE = 1.25f;

    const float TEXT_SHADOW_X = 4;
    const float TEXT_SHADOW_Y = 6;
    const float SHADOW_ALPHA = 0.5f;
    const float BUTTON_SHADOW_X = 8;
    const float BUTTON_SHADOW_Y = 8;
    

    Vector2 view = g->getViewport();

    g->push();
    g->translate(tx, ty);
    g->useTransf();

    float dx = view.x/2 - rendw/2;
    float dy = view.y/2 - rendh/2;

    float bw = blockSize.x + xoff;
    float bh = blockSize.y + yoff;

    // Draw blocks
    float nscale;
    float cx, cy;
    float s;
    float textScale;
    float col;
    for(int y = 0; y < height; ++ y) {

        for(int x = 0; x < width; ++ x) {

            nscale = 1.0f;
            if(cpos.x == x && cpos.y == y) {

                nscale = 1.25f;
                col = 1.0f;
            }
            else {

                col = DARKEN;
            }
            blockScale[y*width+x].target = nscale;
            s = blockScale[y*width+x].scale;

            cx = dx + x*bw + bw/2;
            cy = dy + y*bh + bh/2;

            // Draw block shadow
            g->setColor(0, 0, 0, SHADOW_ALPHA);
            g->drawBitmap(bmpBlocks,0,0,128,128,
                cx - blockSize.x/2*s + BUTTON_SHADOW_X, 
                cy - blockSize.y/2*s + BUTTON_SHADOW_Y,
                blockSize.x*s, blockSize.y*s);

            // Draw block
            g->setColor(col, col, col);
            g->drawBitmap(bmpBlocks,0,0,128,128,
                cx - blockSize.x/2*s, cy - blockSize.y/2*s,
                blockSize.x*s, blockSize.y*s);

            // Draw number
            textScale = TEXT_BASE_SCALE* blockSize.x/128.0f * s;
            g->drawText(bmpFont, intToString(x+y*width +1),
                cx+xoff/2, cy-32.0f*textScale, 
                TEXT_XOFF, 0, 
                TEXT_SHADOW_X*textScale,
                TEXT_SHADOW_Y*textScale, 
                SHADOW_ALPHA, textScale, 
                true);
        }
    }

    g->pop();
    g->useTransf();
    g->setColor();
}
