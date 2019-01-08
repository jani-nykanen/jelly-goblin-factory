// Read PNG
// (c) 2019 Jani Nykänen

#ifndef __READ_PNG_H__
#define __READ_PNG_H__

#include <string>

// Read a PNG file
unsigned char* readPNG(std::string path, int &width, int &height);

#endif // __READ_PNG_H__
