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
	glDrawElements(GL_TRIANGLES, rectMesh.indexCount, 
        GL_UNSIGNED_SHORT, (void*)0);
}
