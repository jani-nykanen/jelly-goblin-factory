// Asset pack
// (c) 2019 Jani Nykänen

#ifndef __ASSET_PACK_H__
#define __ASSET_PACK_H__

#include "Bitmap.hpp"

#include <string>
#include <vector>

// Types
namespace AssetType {

    enum {
        Bitmap = 0
    };
}

// Generic asset
template<class T> struct Asset {

    T asset;
    std::string name;

    // Constructor
    inline Asset() {}
    inline Asset(T asset, std::string name) {

        this->asset = asset;
        this->name = name;
    }
};

// Asset pack
class AssetPack {

private:

    // Bitmaps
    // TODO: Make pointer?
    std::vector<Asset<Bitmap*> > bitmaps;

    // Needed for parsing
    std::string basePath;
    int assetType;

    // Handle special parameter
    void handleSpecialParam(std::string key, std::string value);

public:

    // Constructor
    AssetPack(std::string path);
    // Desctructor
    ~AssetPack();

    // Get a bitmap by its name
    Bitmap* getBitmap(std::string name);
};

#endif // __ASSET_PACK_H__
