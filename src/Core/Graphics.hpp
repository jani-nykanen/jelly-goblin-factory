// Graphics context & routines
// (c) 2019 Jani Nykänen

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "GraphicsCore.hpp"

// Flipping flags
namespace Flip {

    enum {

        None = 0,
        Horizontal = 1,
        Vertical = 2,
        Both = Horizontal | Vertical,
    };
}


// Graphics class
class Graphics : public GraphicsCore {

private:

    // Alpha
    uint8 alpha;

    // Clip
    bool clip(int &sx, int &sy, int &sw, int &sh, int &dx, int &dy, int flip);
    bool clip(int &x, int &y, int &w, int &h);

public:

    // Constructor
    Graphics(int canvasWidth, int canvasHeight);

    // Set alpha
    inline void setAlpha(uint8 v) {alpha=v;}
    // Get alpha
    inline uint8 getAlpha() {return alpha;}

    // Clear screen
    void clearScreen(uint8 color);

    // Draw a filled rectangle
    void fillRect(int x, int y, int w, int h, uint8 color);

    // Draw a bitmap (fast)
    void drawBitmapFast(Bitmap* bmp, int sx, int sy, int sw, int sh, int dx, int dy);
    void drawBitmapFast(Bitmap* bmp, int dx, int dy);
    // Draw a bitmap (with alpha & flipping)
    void drawBitmap(Bitmap* bmp, int sx, int sy, int sw, int sh, 
        int dx, int dy, int flip = 0);
    void drawBitmap(Bitmap* bmp, int dx, int dy, int flip = 0);

    // Draw text
    void drawText(Bitmap* bmp, std::string text, 
        int dx, int dy, int xoff, int yoff, 
        bool center=false);

    // Draw pseudo-3D floor
    void drawPseudo3DFloor(Bitmap* bmp, 
        Vec2Fixed tr, Vec2Fixed scale, int angle,
        int horizon);
};

#endif // __GRAPHICS_H__
