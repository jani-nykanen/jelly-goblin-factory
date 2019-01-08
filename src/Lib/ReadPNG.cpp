// Read PNG
// (c) 2019 Jani Nykänen

#include "ReadPNG.hpp"

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// Read a PNG file
unsigned char* readPNG(std::string path, int &width, int &height) {

    // Load image
    int comp;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &comp, 4);
    if(data == NULL) {

        throw std::runtime_error("Failed to load a bitmap in " + path);
    }

    return data;
}
