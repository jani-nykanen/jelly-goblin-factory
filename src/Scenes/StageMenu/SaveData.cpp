// Save data reading & writing
// (c) 2019 Jani Nykänen

#include "SaveData.hpp"

#include "../../Core/Types.hpp"

#include <cstdio>


// Write data
void SaveDataManager::write(std::vector<int> data) {

    // Convert to bytes
    std::vector<uint8> bytes;
    for(int i = 0; i < data.size(); ++ i) {
        bytes.push_back((uint8)data[i]);
    }

    // Save bytes
    FILE* f = fopen(path.c_str(), "wb");
    if(f == NULL) {

        printf("Failed to write to a file in %s!\n", path.c_str());
        return;
    }

    // Write bytes
    fwrite(&bytes[0], bytes.size(), 1, f);

    // Close
    fclose(f);
}


// Load data
std::vector<int> SaveDataManager::read() {

    std::vector<int> ret;

    // Open a file
    FILE* f = fopen(path.c_str(), "rb");
    if(f == NULL) {

        printf("No save data in %s.\n", path.c_str());

        // We still return something, though
        return ret;
    }

    // Read to a buffer
    uint8 c;
    while(!feof(f)) {

        c = fgetc(f);
        ret.push_back((int)c);
    }

    // Close
    fclose(f);

    return ret;
}
