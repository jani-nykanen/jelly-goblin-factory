// A simple single-layer tilemap
// (NOTE: very ugly & simple, zero error
//  checking!)
// (c) 2019 Jani Nykänen

#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "Types.hpp"

#include <vector>
#include <string>

typedef std::vector<int> Layer;

// Tilemap type
class Tilemap {

private:

    // Data
    std::vector<int> data;
    // Dimensions
    int width;
    int height;

    // Properties
    std::vector<KeyValuePair> properties;

public:

    // Constructor
    Tilemap(std::string path);

    // Get dimensions
    inline int getWidth(){return width;}
    inline int getHeight(){return height;}

    // Get tile
    int getTile(int x, int y);
};

#endif // __TILEMAP_H__
