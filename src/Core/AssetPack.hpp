// Asset pack
// (c) 2019 Jani Nykänen

#ifndef __ASSET_PACK_H__
#define __ASSET_PACK_H__

#include "Bitmap.hpp"
#include "Sample.hpp"
#include "Music.hpp"

#include <string>
#include <vector>


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

    // Assets
    std::vector<Asset<Bitmap*> > bitmaps;
    std::vector<Asset<Sample*> > samples;
    std::vector<Asset<Music*> > music;

    // Needed for parsing
    std::string basePath;
    int assetType;

    // Handle special parameter
    void handleSpecialParam(std::string key, std::string value);

    // Get a generic asset
    template <class T> T* getAsset(std::vector<Asset<T*> >* vec, 
            std::string name);

public:

    // Constructor
    AssetPack(std::string path);
    // Desctructor
    ~AssetPack();

    // Get a bitmap by its name
    Bitmap* getBitmap(std::string name);
    // Get a sample by its name
    Sample* getSample(std::string name);
    // Get a music track by its name
    Music* getMusic(std::string name);
};

#endif // __ASSET_PACK_H__
