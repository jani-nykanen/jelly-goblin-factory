// Graphics core
// (c) 2019 Jani Nykänen

#ifndef __GRAPHICS_CORE_H__
#define __GRAPHICS_CORE_H__

#include "Shader.hpp"

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

    // Canvas content size
    int canvasWidth;
    int canvasHeight;

    // Rectangular mesh
    SimpleMesh* rectMesh =NULL;

    // Canvas texture
    uint32 texCanvas;
    // Canvas data
    uint8* canvasData;

    // Create rectangular mesh
    void createRectMesh();
    // Create canvas texture
    void createCanvasTexture();

    // Compute canvas properties
    void computeCanvasProp(int w, int h);

public:

    // Constructor
    GraphicsCore(int canvasWidth, int canvasHeight);
    // Destructor
    ~GraphicsCore();

    // Resize event
    void resize(int width, int height);

    // Draw canvas
    void drawCanvas();

};

#endif // __GRAPHICS_CORE_H__
