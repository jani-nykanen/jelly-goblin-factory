// Graphics context & routines
// (c) 2019 Jani Nykänen

#include "Graphics.hpp"

#include "MathExt.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <cstring>
#include <cstdio>


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

    shader->setColorUniforms(Color(r, g, b, a));
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

    drawBitmap(bmp, sx, sy, sw, sh, dx, dy, 
        bmp->getWidth(), bmp->getHeight(), 
        flip);
}
void Graphics::drawBitmap(Bitmap* bmp, float dx, float dy, float dw, float dh,
        int flip) {

    drawBitmap(bmp, 0, 0, bmp->getWidth(), bmp->getHeight(), dx, dy, dw, dh, flip);
}
void Graphics::drawBitmap(Bitmap* bmp, float dx, float dy, int flip) {

    drawBitmap(bmp, dx, dy, bmp->getWidth(), bmp->getHeight(), flip);
}
