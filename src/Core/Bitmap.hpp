// Bitmap
// (c) 2019 Jani Nykänen

#ifndef __BITMAP_H__
#define __BITMAP_H__

#include "Types.hpp"

#include <string>

// Bitmap class
class Bitmap {

private:

    // Dimensions
    int width;
    int height;
    // Texture
    uint32 texture;

    // Create
    void create(int width, int height, uint8* data);

public:

    // Constructors
    Bitmap(int width, int height);
    Bitmap(int width, int height, uint8* data);
    Bitmap(std::string path);
    // Destructor
    ~Bitmap();

    // Bind
    void bind();

    // Getters
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    inline uint32 getTexture() { return texture; }
};

#endif // __BITMAP_H__
