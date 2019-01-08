// Mesh
// (c) 2019 Jani Nykänen

#include "Mesh.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

// Constructor
Mesh::Mesh(float* vertices, float* uvs, uint16* indices,
    int vertexCount, int uvCount, int indexCount) {

    // Generate buffers
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &uvBuffer);
    glGenBuffers(1, &indexBuffer);

    // Set buffers
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), 
        (const void*)vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvCount * sizeof(float), 
        (const void*)uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint16), 
        (const void*)indices, GL_STATIC_DRAW);  

    this->indexCount = indexCount;
}


// Bind
void Mesh::bind() {

    // Bind buffers for use
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
		
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer( 0, 2, GL_FLOAT, false, 0, (void*)0);
		
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer( 1, 2, GL_FLOAT, false, 0, (void*)0);
		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}


// Draw
void Mesh::draw() {

    glDrawElements(GL_TRIANGLES, indexCount, 
        GL_UNSIGNED_SHORT, (void*)0);
}
