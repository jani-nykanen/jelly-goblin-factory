// Bitmap
// (c) 2019 Jani Nykänen

#include "Bitmap.hpp"

#include <cstdio>
#include <algorithm>
#include <iterator>
#include <stdexcept>


// Create
void Bitmap::create(int width, int height, uint8* src) {
    
    if(src != NULL) {

        // Copy data
        data = new uint8[width*height];
        for(int i = 0; i < width*height; ++ i) {

            data[i] = src[i];
        }
    }
    this->width = width;
    this->height = height;
}


// Constructors
Bitmap::Bitmap(int width, int height) {

    // Allocate memory for the bitmap
    data = new uint8[width*height];
    for(int i = 0; i < width*height; ++ i) {

        data[i] = 0;
    }

    // Create
    create(width, height, NULL);
}
Bitmap::Bitmap(int width, int height, uint8* data) {
    
    // Create
    create(width, height, data);
}
Bitmap::Bitmap(std::string path) {

    // Load from a file
    // Open file
    FILE* f = fopen(path.c_str(), "rb");
    if(f == NULL) {

        throw new std::runtime_error("Failed to load a file in: "
        + path);
    }

    // Read size
    short w, h;
    fread(&w, sizeof(short),1, f);
    fread(&h, sizeof(short),1, f);

    // Allocate memory
    data = new uint8[w*h];

    // Read data
    fread(data, sizeof(uint8), w*h, f);

    // Store dimensions
    width = (int)w;
    height = (int)h;

    // Close file
    fclose(f);
}


// Destructor
Bitmap::~Bitmap() {

    delete[] data;
}
