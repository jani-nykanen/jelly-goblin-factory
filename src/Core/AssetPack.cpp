// Asset pack
// (c) 2019 Jani Nykänen

#include "AssetPack.hpp"

#include "Config.hpp"


// Types
namespace AssetType {

    enum {
        Bitmap = 0,
        Sample = 1,
        Music = 2,
    };
}


// Handle special parameter
void AssetPack::handleSpecialParam(std::string key, std::string value) {

    // Set base path
    if(key == "path") {

        basePath = value;
    }
    // Set asset type
    else if(key == "type") {

        if(value == "bitmap") {

            assetType = AssetType::Bitmap;
        }
        else if(value == "sample") {

            assetType = AssetType::Sample;
        }
        else if(value == "music") {

            assetType = AssetType::Music;
        }
    }
}

// Get a generic asset
template <class T> T* AssetPack::getAsset(std::vector<Asset<T*> >* vec, 
    std::string name) {

    for(int i = 0; i < vec->size(); ++ i) {

        if((*vec)[i].name == name) {

            return (*vec)[i].asset;
        }
    }

    return NULL;
}


// Constructor
AssetPack::AssetPack(std::string path) {

    ConfigData data = ConfigData(path);
    
    // Create data
    bitmaps = std::vector<Asset<Bitmap*> > ();

    // Go through params
    std::string key, value;
    std::string assetName, assetPath;
    for(int i = 0; i < data.getParamCount(); ++ i) {

        // Check if a special parameter
        key = data.getKey(i);
        value = data.getParam(i);
        if(key[0] == '@') {

            handleSpecialParam(key.substr(1), value);
        }
        else {

            // Set params
            assetName = key;
            assetPath = basePath + value;

            // Load assets
            switch(assetType) {

            // Load bitmap
            case AssetType::Bitmap:
                bitmaps.push_back(Asset<Bitmap*> (new Bitmap(assetPath), assetName));
                break;

            // Load sample
            case AssetType::Sample:
                samples.push_back(Asset<Sample*> (new Sample(assetPath), assetName));

            // Load music
            case AssetType::Music:
                music.push_back(Asset<Music*> (new Music(assetPath), assetName));

            default:
                break;    
            }
        }
    }
}


// Desctructor
AssetPack::~AssetPack() {

    // Destroy bitmaps
    for(int i = 0; i < bitmaps.size(); ++ i) {

        delete bitmaps[i].asset;
    }

    // Destroy samples
    for(int i = 0; i < samples.size(); ++ i) {

        delete samples[i].asset;
    }

    // Destroy music
    for(int i = 0; i < music.size(); ++ i) {

        delete music[i].asset;
    }
}


// Get a bitmap by its name
Bitmap* AssetPack::getBitmap(std::string name) {

    return getAsset<Bitmap>(&bitmaps, name);
}


// Get a sample by its name
Sample* AssetPack::getSample(std::string name) {

    return getAsset<Sample>(&samples, name);
}


// Get a music track by its name
Music* AssetPack::getMusic(std::string name) {

    return getAsset<Music> (&music, name);
}
