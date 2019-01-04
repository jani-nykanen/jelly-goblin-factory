// Bitmap
// (c) 2019 Jani Nykänen

#ifndef __BITMAP_H__
#define __BITMAP_H__

#include "Types.hpp"

// Bitmap class
class Bitmap {

private:

    // Dimensions
    int width;
    int height;
    // Data
    uint8* data;

    // Create
    void create(int width, int height, uint8* data);

public:

    // Constructors
    Bitmap(int width, int height);
    Bitmap(int width, int height, uint8* data);
    // Destructor
    ~Bitmap();

    // Getters
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    inline uint8* getData() { return data; }
};

#endif // __BITMAP_H__
