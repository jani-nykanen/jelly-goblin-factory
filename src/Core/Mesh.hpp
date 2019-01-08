// Mesh
// (c) 2019 Jani Nykänen

#ifndef __MESH_H__
#define __MESH_H__

#include "Types.hpp"

// Mesh type
class Mesh {

private:

    // Buffers
    uint32 vertexBuffer;
    uint32 uvBuffer;
    uint32 indexBuffer;
    uint32 indexCount;

public:

    // Constructor
    Mesh(float* vertices, float* uvs, uint16* indices,
        int vertexCount, int uvCount, int indexCount);

    // Bind
    void bind();

    // Draw
    void draw();
};

#endif // __MESH_H__
