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
    float uvs[] = {0,0, 1,0, 1,1, 0,1};
    uint16 indices[] = {0,1,2, 2,3,0};

    // Create mesh
    rectMesh = new Mesh(
        vertices, uvs, indices,
        2*4, 2*4, 6
    );

    // Bind for use
    rectMesh->bind();
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
    delete rectMesh;
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
