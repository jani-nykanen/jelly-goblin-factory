// Graphics core
// (c) 2019 Jani Nykänen

#ifndef __GRAPHICS_CORE_H__
#define __GRAPHICS_CORE_H__

#include "Shader.hpp"

#define GRAPHICS_CORE_PALETTE_SIZE 256

// Simple mesh
struct SimpleMesh {
    uint32 vertexBuffer;
    uint32 uvBuffer;
    uint32 indexBuffer;
    uint32 indexCount;
};

// A very primitive rect class
typedef struct {
    float x;
    float y;
    float w;
    float h;
} PrimitiveRect;


// Graphics class
class GraphicsCore {

private:

    // Shader
    Shader* shader =NULL;

    // Rectangular mesh
    SimpleMesh rectMesh;

    // Canvas texture
    uint32 texCanvas;
    // Canvas pixel data
    uint8* canvasPixels;
    
    // Palette
    uint8 palette[GRAPHICS_CORE_PALETTE_SIZE *3];

    // Create rectangular mesh
    void createRectMesh();
    // Create canvas texture
    void createCanvasTexture();
    // Generate palette
    void genPalette();

    // Compute canvas properties
    void computeCanvasProp(int w, int h);

protected:

    // Canvas content size
    int canvasWidth;
    int canvasHeight;

    // Canvas framebuffer
    uint8* canvasFramebuffer;

public:

    // Constructor
    GraphicsCore(int canvasWidth, int canvasHeight);
    // Destructor
    ~GraphicsCore();

    // Resize event
    void resize(int width, int height);

    // Draw canvas
    void drawCanvas();
    // Refresh canvas
    void refreshCanvas();

};

#endif // __GRAPHICS_CORE_H__
