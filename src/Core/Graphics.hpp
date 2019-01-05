// Graphics context & routines
// (c) 2019 Jani Nykänen

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Shader.hpp"


// Simple mesh
struct SimpleMesh {
    uint32 vertexBuffer;
    uint32 uvBuffer;
    uint32 indexBuffer;
    uint32 indexCount;
};


// Graphics class
class Graphics {

private:

    // Shader
    Shader* shader;

    // Framebuffer size
    int fbWidth;
    int fbHeight;

    // Rectangular mesh
    SimpleMesh* rectMesh;

    // Create rectangular mesh
    void createRectMesh();

public:

    // Constructor
    Graphics(int canvasWidth, int canvasHeight);
    // Destructor
    ~Graphics();

    // Resize event
    void resize(int width, int height);

    // Draw canvas
    void drawCanvas();

};

#endif // __GRAPHICS_H__
