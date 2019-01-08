// Graphics core
// (c) 2019 Jani Nykänen

#ifndef __GRAPHICS_CORE_H__
#define __GRAPHICS_CORE_H__

#include "Shader.hpp"
#include "Bitmap.hpp"
#include "Mesh.hpp"
#include "Transformations.hpp"


// Graphics class
class GraphicsCore : public Transformations {

private:

    // Create rectangular mesh
    void createRectMesh();

protected:

    // Shader
    Shader* shader =NULL;

    // Rectangular mesh
    Mesh* rectMesh;
    // White texture
    Bitmap* bmpWhite;

public:

    // Constructor
    GraphicsCore();
    // Destructor
    ~GraphicsCore();

    // Resize event
    void resize(int width, int height);

    // Use transformations
    void useTransf();
};

#endif // __GRAPHICS_CORE_H__
