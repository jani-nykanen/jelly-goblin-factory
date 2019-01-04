// Bitmap
// (c) 2019 Jani Nykänen

#include "Bitmap.hpp"

#include <cstdio>
#include <algorithm>
#include <iterator>


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


// Destructor
Bitmap::~Bitmap() {

    delete[] data;
}
