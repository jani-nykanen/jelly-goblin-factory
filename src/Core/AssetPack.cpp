// Asset pack
// (c) 2019 Jani Nykänen

#include "AssetPack.hpp"

#include "Config.hpp"


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
    }
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
}


// Get a bitmap by its name
Bitmap* AssetPack::getBitmap(std::string name) {

    for(int i = 0; i < bitmaps.size(); ++ i) {

        if(bitmaps[i].name == name) {

            return bitmaps[i].asset;
        }
    }

    return NULL;
}
