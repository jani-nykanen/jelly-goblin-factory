// Graphics context & routines
// (c) 2019 Jani Nykänen

#include "Graphics.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <cstring>
#include <cstdio>

// Constants
static const uint8 DEFAULT_ALPHA = 170;


// Clip
bool Graphics::clip(int &sx, int &sy, int &sw, int &sh, int &dx, int &dy, int flip) {

    int fw = frame->getWidth();
    int fh = frame->getHeight();

    // Check if we have anything to draw
    if(dx+sw < 0 || dx >= fw || dy+sh <= 0 || dy >= fh)
        return false;

    bool hflip = (flip & Flip::Horizontal) != 0;
    bool vflip = (flip & Flip::Vertical) != 0;
    int ow, oh;

    // Horizontal
    if(dx+sw >= fw) {

		ow = sw;
		sw = (fw - dx);
		if(hflip) {

			sx += ow - sw;
		}

	} 
    if(dx < 0) {

		ow = sw;
		sx += -dx;
		sw += dx;
		dx = 0;
		if(hflip) {

			sx += sw - ow;
		}
	}

    // Vertical
	if(dy+sh >= fh) {

		oh = sh;
		sh = fh - dy;
		if(vflip) {

			sy += oh - sh;
		}

	} 
    if(dy < 0) {

		oh = sh;
		sy += -dy;
		sh += dy;
		dy = 0;
		if(vflip) {

			sy += sh - oh;
		}
	}
    return true;
}
bool Graphics::clip(int &x, int &y, int &w, int &h) {

    int sx = 0;
    int sy = 0;
    return clip(sx, sy, w, h, x, y, 0);
}


// Constructor
Graphics::Graphics(int canvasWidth, int canvasHeight) 
    : GraphicsCore(canvasWidth, canvasHeight) {

    // Set defaults
    alpha = DEFAULT_ALPHA;
}


// Clear screen
void Graphics::clearScreen(uint8 color) {

    memset(frame->getData(), color, canvasWidth*canvasHeight);
}


// Draw a filled rectangle
void Graphics::fillRect(int x, int y, int w, int h, uint8 color) {

    uint8* d = frame->getData();
    int fw = frame->getWidth();

    if(!clip(x, y, w, h)) return;

    // Copy rectangle lines to the framebuffer
    int offset = y*fw + x;
    for(int i = 0; i < h; ++ i) {

        memset((uint8*)(d + offset), color, w);
        offset += fw;
    }
}


// Draw a bitmap (fast)
void Graphics::drawBitmapFast(Bitmap* bmp, int sx, int sy, int sw, int sh, 
    int dx, int dy) {

    if(!clip(sx, sy, sw, sh, dx, dy, Flip::None))
        return;

    uint8* d = frame->getData();
    uint8* bd = bmp->getData();
    int fw = frame->getWidth();
    int bw = bmp->getWidth();

    // Copy bitmap lines to the framebuffer
    int offset = dy*fw + dx;
    int srcOffset = sy*bw + sx;
    for(int i = 0; i < sh; ++ i) {

        memcpy((uint8*)(d+offset), (uint8*)(bd + srcOffset), bw);
        offset += fw;
        srcOffset += bw;
    }
}
void Graphics::drawBitmapFast(Bitmap* bmp, int dx, int dy) {

    drawBitmapFast(bmp, 0, 0, bmp->getWidth(), bmp->getHeight(), dx, dy);
}


// Draw a bitmap
void Graphics::drawBitmap(Bitmap* bmp, int sx, int sy, int sw, int sh, 
    int dx, int dy, int flip) {

    uint8* d = frame->getData();
    uint8* bd = bmp->getData();
    int fw = frame->getWidth();
    int bw = bmp->getWidth();

    int x, y;
    int offset, srcOffset;
    uint8 col;

    bool hflip = (flip & Flip::Horizontal) != 0;
    bool vflip = (flip & Flip::Vertical) != 0;

    // Clip
    if(!clip(sx, sy, sw, sh, dx, dy, flip))
        return;

    offset = fw*dy + dx;
    srcOffset = bw*sy + sx;

    // Vertical flip
    if(vflip) {

        offset += (sh-1) *fw;
    }
    // Horizontal flip
    if(hflip) {

        offset += sw -1;
    }

    // Draw pixels
    for(y = 0; y < sh; ++ y) {

        for(x = 0; x <  sw; ++ x) {

            col = bd[srcOffset ++];

            if(col != alpha)
                d[offset] = col;

            if(hflip)
                -- offset;
            else
                ++ offset;

        }

        srcOffset += bw - sw;

        if(hflip) {

            offset += sw * 2;
        }

        offset -= sw;

        if(vflip) {

            offset -= fw; 
        }
        else {

            offset += fw; 
        }
    }
}
void Graphics::drawBitmap(Bitmap* bmp, int dx, int dy, int flip) {

    drawBitmap(bmp, 0, 0, bmp->getWidth(), bmp->getHeight(), dx, dy, flip);
}


// Draw text
void Graphics::drawText(Bitmap* bmp, std::string text, 
    int dx, int dy, int xoff, int yoff, 
    bool center) {

    int len = text.length();
    int x = dx;
    int y = dy;
    int cw = bmp->getWidth() / 16;
    int ch = cw;
    uint8 c;
    int sx;
    int sy;

    // Center text
    if(center) {

        dx -= (len+1) * (cw+xoff) / 2;
        x = dx;
    }

    // Draw characters
    for(int i = 0; i < len;  ++ i) {

        c = text[i];
        // Newline
        if(c == '\n') {

            x = dx;
            y += yoff + ch;
            continue;
        }

        sx = c % 16;
        sy = c / 16;

        // Draw character
        drawBitmap(bmp, sx*cw, sy*ch, cw, ch, x, y, Flip::None);

        x += cw + xoff;
    }
}