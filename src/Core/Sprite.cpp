// An animated sprite
// (c) 2019 Jani Nykänen

#include "Sprite.hpp"


// Constructor
Sprite::Sprite(int w, int h) {

    width = w;
    height = h;

    row = 0;
    frame = 0;
    count = 0.0f;
}


// Animate
void Sprite::animate(int row, int start, int end, float speed, float tm) {

    // If starting & ending frame are the same
	if (start == end) {

        count = 0;
        frame = start;
        this->row = row;
        return;
    }

    // Set to the current frame and start
    // animation from the beginning
    if (this->row != row) {

        count = 0;
        frame = end > start ? start : end;
        this->row = row;
    }

    if (start < end && frame < start) {

        frame = start;
    }
    else if (end < start && frame < end) {

    frame = end;
    }

    // Animate
    count += 1.0f * tm;
    if (count > speed) {

        if (start < end) {

            if (++frame > end) {
                
                frame = start;
            }
        }
        else {

            if (--frame < end)
                frame = start;        
        }
        count -= speed;
    }
}
// Set frame
void Sprite::setFrame(int row, int frame) {

    this->row = row;
    this->frame = frame;
    count = 0.0f;
}


// Draw
void Sprite::draw(Graphics* g, Bitmap* bmp, int frame, int row, 
        float x, float y, int flip) {

    g->drawBitmap(bmp, width * frame, height * row, 
        width, height, x, y, flip);
}
void Sprite::draw(Graphics* g, Bitmap* bmp, float x, float y, int flip ){

    draw(g, bmp, frame, row, x, y, flip);
}
    
