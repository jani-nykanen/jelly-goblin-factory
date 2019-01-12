// An animated sprite
// (c) 2019 Jani Nykänen

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Graphics.hpp"

// Sprite class
class Sprite {

private:

    // Dimensions
    int width;
    int height;

    // Animation properties
    int frame;
    int row;
    float count;

public:

    // Constructor
    inline Sprite() {}
    Sprite(int w, int h);

    // Animate
    void animate(int row, int start, int end, float speed, float tm);
    // Set frame
    void setFrame(int row, int frame);

    // Draw
    void draw(Graphics* g, Bitmap* bmp, int frame, int row, 
        float x, float y, int flip = 0);
    void draw(Graphics* g, Bitmap* bmp, float x, float y, int flip = 0);

    // Getters
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    inline int getFrame() {return frame;}
    inline int getRow() {return row;}

    // Setters
    inline void setRow(int r) {row = r;}
};


#endif // __SPRITE_H__
