// Bitmap
// (c) 2019 Jani Nykänen

#include "Bitmap.hpp"

#include <cstdio>
#include <algorithm>
#include <iterator>
#include <stdexcept>

#include <GL/gl.h>

#include "../Lib/ReadPNG.hpp"

// Previous texture
static Bitmap* prevTex = NULL;


// Create
void Bitmap::create(int width, int height, uint8* src) {

    // Store dimensions
    this->width = width;
    this->height = height;

    // Create texture
    glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
	    GL_UNSIGNED_BYTE, src);
}


// Constructors
Bitmap::Bitmap(int width, int height) {

    const int CHANNELS = 4;

    // Allocate memory for the bitmap
    uint8* data = new uint8[width*height*CHANNELS];
    for(int i = 0; i < width*height*CHANNELS; ++ i) {

        data[i] = 255;
    }

    // Create
    create(width, height, data);

    // Clear data
    delete[] data;
}
Bitmap::Bitmap(int width, int height, uint8* data) {
    
    // Create
    create(width, height, data);
}
Bitmap::Bitmap(std::string path) {

    uint8* data = readPNG(path, width, height);
    create(width, height, data);
    free(data);
}


// Destructor
Bitmap::~Bitmap() {

    // ...
}


// Bind
void Bitmap::bind() {

    if(prevTex != this) {

        prevTex = this;
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}
