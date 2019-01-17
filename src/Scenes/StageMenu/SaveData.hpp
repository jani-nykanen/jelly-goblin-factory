// Save data reading & writing
// (c) 2019 Jani Nykänen

#ifndef __SAVE_DATA_H__
#define __SAVE_DATA_H__

#include <vector>
#include <string>

// Save data manager
class SaveDataManager {

    // File path
    std::string path;

public:

    // Constructor
    inline SaveDataManager(){}
    inline SaveDataManager(std::string path) {
        this->path = path;
    }

    // Write data
    void write(std::vector<int> data);
    // Load data
    std::vector<int> read();

};

#endif // __SAVE_DATA_H__
