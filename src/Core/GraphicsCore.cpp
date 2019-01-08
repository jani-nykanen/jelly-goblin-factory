// Graphics core
// (c) 2019 Jani Nykänen

#include "GraphicsCore.hpp"

#include "MathExt.hpp"

#include <GL/glew.h>
#include <GL/gl.h>


// Create rectangular mesh
void GraphicsCore::createRectMesh() {

    // Data
    float vertices[] = {0,0, 1,0, 1,1, 0,1};
    float uvs[] = {0,1, 1,1, 1,0, 0,0};
    uint16 indices[] = {0,1,2, 2,3,0};

    // Generate buffers
    glGenBuffers(1, &rectMesh.vertexBuffer);
    glGenBuffers(1, &rectMesh.uvBuffer);
    glGenBuffers(1, &rectMesh.indexBuffer);

    // Set buffers
    glBindBuffer(GL_ARRAY_BUFFER, rectMesh.vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), 
        (const void*)vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, rectMesh.uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), 
        (const void*)uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectMesh.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint16), 
        (const void*)indices, GL_STATIC_DRAW);  

    rectMesh.indexCount = 6;

    // Bind buffers for use
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
		
	glBindBuffer(GL_ARRAY_BUFFER, rectMesh.vertexBuffer);
	glVertexAttribPointer( 0, 2, GL_FLOAT, false, 0, (void*)0);
		
	glBindBuffer(GL_ARRAY_BUFFER, rectMesh.uvBuffer);
	glVertexAttribPointer( 1, 2, GL_FLOAT, false, 0, (void*)0);
		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectMesh.indexBuffer);
}


// Constructor
GraphicsCore::GraphicsCore() : Transformations() {

    // Enable & set GL settings
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
	glDisable(GL_DEPTH_TEST);
	glEnable( GL_BLEND );
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, 
        GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // Create shader
    shader = new Shader();
    // Use it
    shader->useShader();

    // Create rectangular mesh
    createRectMesh();
    // Create white texture
    bmpWhite = new Bitmap(1, 1);
}


// Destructor
GraphicsCore::~GraphicsCore() {

    delete shader;
    delete bmpWhite;
}


// Resize event
void GraphicsCore::resize(int width, int height) {

    // Pass size to the transformations
    fbSize = Vector2(width, height);

    // Resize viewport
    glViewport(0, 0, width, height);
}


// Use transformations
void GraphicsCore::useTransf() {

    passToShader(shader);
}
