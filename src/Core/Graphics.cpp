// Graphics context & routines
// (c) 2019 Jani Nykänen

#include "Graphics.hpp"

#include "MathExt.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <cstring>
#include <cstdio>
#include <stdexcept>


// Constructor
Graphics::Graphics() : GraphicsCore() {

    // ...
}


// Clear screen
void Graphics::clearScreen(float r, float g, float b) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, 1.0f);
}



// Set color
void Graphics::setColor(float r, float g, float b, float a) {

    gcolor = Color(r, g, b, a);
    shader->setColorUniforms(gcolor);
}


// Draw a filled rectangle
void Graphics::fillRect(float x, float y, float w, float h) {

    // Bind texture
	bmpWhite->bind();
		
	// Pass position & dimension data to the shader
	shader->setVertexUniforms(Vector2(x, y), Vector2(w, h));
	shader->setUVUniforms(Vector2(0, 0), Vector2(1, 1));
	
    // Draw
	rectMesh->draw();
}


// Draw a bitmap
void Graphics::drawBitmap(Bitmap* bmp, float sx, float sy, float sw, float sh, 
        float dx, float dy, float dw, float dh, int flip) {

        if(bmp == NULL) {

            throw std::runtime_error("Null bitmap error!");
        }

        // Bind bitmap
		bmp->bind();
		
		// Flip
		float w = (float)bmp->getWidth();
	    float h = (float)bmp->getHeight();
	    if( (flip & Flip::Horizontal) != 0) {

	        dx += dw;
	        dw *= -1;
	    }
	    if( (flip & Flip::Vertical) != 0) {

	        dy += dh;
	        dh *= -1;
	    }

        // Pass data to shaders
        shader->setVertexUniforms(Vector2(dx, dy), Vector2(dw, dh));
	    shader->setUVUniforms(Vector2(sx / w , sy / h ), 
            Vector2(sw / w , sh / h));
	    
        // Draw
	    rectMesh->draw();
}
void Graphics::drawBitmap(Bitmap* bmp, float sx, float sy, float sw, float sh, 
        float dx, float dy, 
        int flip) {

    if(bmp == NULL) {
        throw std::runtime_error("Null bitmap error!");
    }

    drawBitmap(bmp, sx, sy, sw, sh, dx, dy, 
        sw, sh, 
        flip);
}
void Graphics::drawBitmap(Bitmap* bmp, float dx, float dy, float dw, float dh,
        int flip) {
    
    if(bmp == NULL) {
        throw std::runtime_error("Null bitmap error!");
    }
    drawBitmap(bmp, 0, 0, bmp->getWidth(), bmp->getHeight(), dx, dy, dw, dh, flip);
}
void Graphics::drawBitmap(Bitmap* bmp, float dx, float dy, int flip) {

    if(bmp == NULL) {
        throw std::runtime_error("Null bitmap error!");
    }
    drawBitmap(bmp, dx, dy, bmp->getWidth(), bmp->getHeight(), flip);
}

// Draw text
void Graphics::drawText(Bitmap* bmp, std::string text, int dx, int dy, 
                int xoff, int yoff, 
		        float scale, bool center) {

    if(bmp == NULL) {
        throw std::runtime_error("Null bitmap error!");
    }

    int cw = (bmp->getWidth()) / 16;
    int ch = cw;
    int len = text.length();

    float x = dx;
    float y = dy;
    unsigned char c;

    // Center the text
    if (center)
    {
        dx -= ((len + 1) / 2.0f * (cw + xoff) * scale);
        x = dx;
    }

    // Draw every character
    float sx, sy;
    for (int i = 0; i < len; ++i)
    {

        c = text[i];
        // Line swap
        if (c == '\n')
        {

            x = dx;
            y += (yoff + ch) * scale;
            continue;
        }

        sx = c % 16;
        sy = (c / 16);
        // Draw character
        drawBitmap(bmp, sx * cw, sy * ch, cw, ch,
            x, y,
            cw * scale, ch * scale);

        x += (cw + xoff) * scale;
    } 
}


// Draw text with a shadow
void Graphics::drawText(Bitmap* bmp, std::string text, int dx, int dy, 
                int xoff, int yoff, 
		        float shadowX, float shadowY,
                float trans, float scale,
                bool center) {

    Color c = gcolor;

    // Draw shadow
    setColor(0, 0, 0, trans);
    drawText(bmp, text, dx + shadowX, dy + shadowY, 
        xoff, yoff, scale, center);    

    // Draw base text
    setColor(c.r, c.g, c.b, c.a);
    drawText(bmp, text, dx, dy, xoff, yoff, scale, center);    
}