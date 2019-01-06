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


// Create canvas texture
void GraphicsCore::createCanvasTexture() {

    const int CHANNELS = 3;

    // Generate palette
    genPalette();

    // Create data
    canvasPixels = new uint8[canvasWidth*canvasHeight*CHANNELS];
    for(int i = 0; i < canvasWidth*canvasHeight*CHANNELS; ++ i) {

        canvasPixels[i] = 255;
    }
    frame = new Bitmap(canvasWidth, canvasHeight);

    // Create texture
    glGenTextures(1, &texCanvas);
    glBindTexture(GL_TEXTURE_2D, texCanvas);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, canvasWidth, canvasHeight, 0, GL_RGB,
	    GL_UNSIGNED_BYTE, canvasPixels);

    glActiveTexture(GL_TEXTURE0);
}   


// Generate palette
void GraphicsCore::genPalette() {

    uint8 col, r,g,b;
    for(int i = 0; i < GRAPHICS_CORE_PALETTE_SIZE; ++ i) {

        col = (uint8)i;

        // Get components
        r = col >> 5;
        r *= 36;
        g = col << 3;
        g = g >> 5;
        g *= 36;
        b = col << 6;
        b = b >> 6;
        b *= 85;

        // Make the colors "imitate VGA
        // colors"
        r /= 4; r *= 4;
        g /= 4; g *= 4;
        b /= 4; b *= 4;

        palette[i*3] = r;
        palette[i*3 +1] = g;
        palette[i*3 + 2] = b;
    }
}


// Compute canvas properties
void GraphicsCore::computeCanvasProp(int w, int h) {

    PrimitiveRect canvasProp;

    float aspectRatio = (float)canvasWidth / (float)canvasHeight;
    float winRatio = (float)w / (float)h;

    // Horizontal
    if(winRatio >= aspectRatio) {

        canvasProp.w = aspectRatio / winRatio * 2.0f;
        canvasProp.h = 2.0f;

        canvasProp.x = -canvasProp.w/2.0f;
        canvasProp.y = -1.0f;
    }
    else {

        canvasProp.w = 2.0f;
        canvasProp.h = winRatio / aspectRatio * 2.0f;

        canvasProp.x = -1.0f;
        canvasProp.y = -canvasProp.h/2.0f;
    }

    // Pass data to the shader
    shader->setUniforms(canvasProp.x, canvasProp.y,
        canvasProp.w, canvasProp.h);
}


// Constructor
GraphicsCore::GraphicsCore(int canvasWidth, int canvasHeight) {

    this->canvasWidth = canvasWidth;
    this->canvasHeight = canvasHeight;

    // Create shader
    shader = new Shader();
    // Use it
    shader->useShader();

    // Create rectangular mesh
    createRectMesh();
    // Create canvas texture
    createCanvasTexture();
}


// Destructor
GraphicsCore::~GraphicsCore() {

    delete frame;
    delete canvasPixels;

    delete shader;
}


// Resize event
void GraphicsCore::resize(int width, int height) {

    glViewport(0, 0, width, height);
    computeCanvasProp(width, height);
}


// Draw canvas
void GraphicsCore::drawCanvas() {

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1.0f);

    // Draw rectangular mesh
    glDrawElements(GL_TRIANGLES, rectMesh.indexCount,
        GL_UNSIGNED_SHORT, (void*)0 );
}


// Refresh canvas
void GraphicsCore::refreshCanvas() {

    uint8* d = frame->getData();

    // Update pixel data
    int cindex;
    for(int i = 0; i < canvasWidth*canvasHeight; ++ i) {

        cindex = d[i];

        canvasPixels[i*3] = palette[cindex*3];
        canvasPixels[i*3 +1] = palette[cindex*3 +1];
        canvasPixels[i*3 +2] = palette[cindex*3 +2];
    }

    // Pass to the texture
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, canvasWidth, canvasHeight,
        GL_RGB, GL_UNSIGNED_BYTE, canvasPixels);
}
