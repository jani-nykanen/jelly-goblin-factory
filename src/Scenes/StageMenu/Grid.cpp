// Stage grid
// (c) 2019 Jani Nykänen

#include "Grid.hpp"

#include "../../Core/Utility.hpp"

#include <cmath>

// Constants
static const int MAX_PAGE = 1; // TEMP
static const float MOVE_TIME = 10.0f;


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


// Reset scalings
void Grid::resetBlockScalings() {

    for(int i = 0; i < blockScale.size(); ++ i) {

        blockScale[i].scale = 1.0f;
        blockScale[i].target = 1.0f;
    }
}


// Compute "virtual" cursor pos
void Grid::computeCursorVpos() {

    float t = ctimer / MOVE_TIME; 
    
    float w = blockSize.x + xoff;
    float h = blockSize.y + yoff;

    // Starting & ending points
    Vector2 start = Vector2(
        -rendw/2 + cpos.x*w,
        -rendh/2 + cpos.y*h
    );
    Vector2 end = Vector2(
        -rendw/2 + ctarget.x*w,
        -rendh/2 + ctarget.y*h
    );

    // Compute position
    cvpos.x = start.x*t + (1-t)*end.x;
    cvpos.y = start.y*t + (1-t)*end.y;
}


// Update cursor
bool Grid::updateCursor(float tm) {

    const float FLOAT_SPEED = 0.05f;
    // Update floating
    cfloatTimer += FLOAT_SPEED * tm;
    cfloatTimer = (float)fmod(cfloatTimer, M_PI*2);

    // Update timer
    bool ret = false;
    if(ctimer > 0.0f) {

        ctimer -= 1.0f * tm;
        if(ctimer <= 0.0f) {

            cpos = ctarget;
            ctimer = 0.0f;
        }
        else {

            ret = true;
        }
    }

    // Compute vpos
    computeCursorVpos();

    return ret;
}


// Constructor
Grid::Grid(AssetPack* assets, int w, int h, 
        int blockw, int blockh, int xoff, int yoff) {

    // Get bitmaps
    bmpFont = assets->getBitmap("font");
    bmpBlocks = assets->getBitmap("blocks");

    // Get samples
    sSelect = assets->getSample("select");
    sAccept = assets->getSample("accept");

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
    cpos.x = 1;
    cpos.y = 0;
    ctarget = cpos;
    ctimer = 0.0f;
    cfloatTimer = 0.0f;
    page = 0;
    computeCursorVpos();

    // Set block scales to default
    blockScale = std::vector<BlockScale> (width*height);
    for(int i = 0; i < width*height; ++ i) {

        blockScale[i] = BlockScale();
        blockScale[i].scale = 1.0f;
        blockScale[i].target = blockScale[i].scale;
    }
}


// Update
bool Grid::update(EventManager* evMan, GridCallback numberCb, float tm) {

    const float DELTA = 0.25f;

    // Audio manager
    AudioManager* audio = evMan->getAudioManager();

    // Update block scales
    for(int i = 0; i < blockScale.size(); ++ i) {

        blockScale[i].update(tm);
    }

    // Update cursor
    if(updateCursor(tm)) {

        return false;
    }

    GamePad* vpad = evMan->getController();
    Vector2 stick = vpad->getStick();

    // Update cursor position
    if(stick.x < -DELTA) {

        if(-- ctarget.x < 0)
            ctarget.x += width;
    }
    else if(stick.x > DELTA) {

        if(++ ctarget.x >= width)
            ctarget.x -= width;
    }
    if(stick.y < -DELTA) {

        if(-- ctarget.y < 0)
            ctarget.y += height;
    }
    else if(stick.y > DELTA) {

        if(++ ctarget.y >= height)
            ctarget.y -= height;
    }
    // If something moved
    if(ctarget.x != cpos.x || ctarget.y != cpos.y) {

        // Play sound
        audio->playSample(sSelect, 0.70f);

        ctimer = MOVE_TIME;
        return false;
    }

    // Check button press
    bool pressed = vpad->getButton("start") == State::Pressed ||
        vpad->getButton("accept") == State::Pressed;

    // TODO: To a different method
    if(pressed) {

        // Play sound
        audio->playSample(sAccept, 0.45f);

        // Next & previous symbols
        if(page != MAX_PAGE && cpos.x == width-1 && 
            cpos.y == height-1) {
        
            ++ page;
            cpos.x = 0;
            cpos.y = 0;
            ctarget = cpos;
            updateCursor(0);

            resetBlockScalings();
        }
        else if(page != 0 && cpos.x == 0 && 
            cpos.y == 0) {
        
            -- page;
            cpos.x = width-1;
            cpos.y = height-1;
            ctarget = cpos;
            updateCursor(0);

            resetBlockScalings();
        }
        // Quit (TEMPORARY!)
        else if(page == 0 && cpos.x == 0 && cpos.y == 0) {

            return true;
        }
        // Number button
        else {

            if(numberCb != NULL) {

                numberCb(getChoseStageIndex());
            }
        }
    }
    return false;
}


// Draw
void Grid::draw(Graphics* g, float tx, float ty, std::vector<int>* completion) {

    const float DARKEN = 0.85f;
    const float BRIGHTEN = 1.10f;
    const float TEXT_XOFF = -32.0f;
    const float TEXT_BASE_SCALE = 1.25f;

    const float TEXT_SHADOW_X = 4;
    const float TEXT_SHADOW_Y = 6;
    const float SHADOW_ALPHA = 0.5f;
    const float BUTTON_SHADOW_X = 8;
    const float BUTTON_SHADOW_Y = 8;

    const float CURSOR_FLOAT_AMPLITUDE = 12.0f;
    const float CURSOR_TRANS_X = 0.75f;
    const float CURSOR_TRANS_Y = 0.5f;
    
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
    std::string num;
    int cval;
    int bx, by;
    for(int y = 0; y < height; ++ y) {

        for(int x = 0; x < width; ++ x) {

            nscale = 1.0f;
            if(cpos.x == x && cpos.y == y) {

                nscale = 1.25f;
                col = BRIGHTEN;
            }
            else {

                col = DARKEN;
            }
            blockScale[y*width+x].target = nscale;
            s = blockScale[y*width+x].scale;

            cx = dx + x*bw + bw/2;
            cy = dy + y*bh + bh/2;

            // Get completion info
            if(isSpecialTile(x, y))
                cval = 0;
            else
                cval = (*completion)[y*width+x + page*width*height -page*2 -1];

            bx = 128 * (cval % 2);
            by = cval/2;
            by *= 128;

            // Draw block shadow
            g->setColor(0, 0, 0, SHADOW_ALPHA);
            g->drawBitmap(bmpBlocks,bx,by,128,128,
                cx - blockSize.x/2*s + BUTTON_SHADOW_X, 
                cy - blockSize.y/2*s + BUTTON_SHADOW_Y,
                blockSize.x*s, blockSize.y*s);

            // Draw block
            g->setColor(col, col, col);
            g->drawBitmap(bmpBlocks,bx,by,128,128,
                cx - blockSize.x/2*s, cy - blockSize.y/2*s,
                blockSize.x*s, blockSize.y*s);

            if(cval > 0)
                continue;

            // Draw number
            num = " ";
            if(page != MAX_PAGE && 
                y == height-1 && x == width-1) {

                num[0] = (char)4;
                cx -= 4;
                cy -= 2;
            }
            else if(x == 0 && y == 0) {

                num[0] = page > 0 ?(char)6 : (char)5;
                cx -= 12;
                cy -= 4;
            }
            else
                num = intToString(y*width+x + page*(width*height) -page*2);

            textScale = TEXT_BASE_SCALE* blockSize.x/128.0f * s;
            g->drawText(bmpFont, num,
                cx+xoff/2, 
                cy-32.0f*textScale, 
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

    // Compute cursor floating
    float cf = (float)sin(cfloatTimer) * CURSOR_FLOAT_AMPLITUDE;
    // Draw cursor
    g->drawBitmap(bmpBlocks, 129, 129, 126, 126,
        view.x/2 + cvpos.x + blockSize.x*CURSOR_TRANS_X, 
        view.y/2 + cvpos.y + blockSize.y*CURSOR_TRANS_Y + cf, 
        blockSize.x, blockSize.y);
}


// Get chosen stage index
int Grid::getChoseStageIndex() {
    
    return cpos.y*width+cpos.x + page*width*height -page*2;
}


// Is the selected tile special
bool Grid::isSpecialTile(int x, int y) {

    return 
        (x == 0 && y == 0)
        || (x == width-1 && y == height-1 && page != MAX_PAGE);
}
bool Grid::isSpecialTile() {

    return isSpecialTile(cpos.x, cpos.y);
}


// Set cursor position
void Grid::setCursorPos(int i) {

    // TODO: Should be while if more than
    // two pages, but to make sure nothing evil
    // happens, let's do the check only once...
    if(page < MAX_PAGE && 
       i >= (page+1)*width*height-1) {

        ++ page;
    }
    i -= page*width*height;
    i += page*2;

    cpos.x = (i % width);
    cpos.y = i / width;
    ctarget = cpos;

    computeCursorVpos();

    ctimer = 0.0f;
}
