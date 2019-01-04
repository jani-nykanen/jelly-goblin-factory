// Configuration file routines
// (c) 2019 Jani Nykänen

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <vector>

// Key-value pair
struct KeyValuePair {
    std::string key;
    std::string value;

    // Constructors
    inline KeyValuePair() {

        this->key = "";
        this->value = "";
    }
    inline KeyValuePair(std::string key, std::string value) {

        this->key = key;
        this->value = value;
    }
};


// Configuration data
class ConfigData {

private:

    // Parameters & their values
    std::vector<KeyValuePair> params;

public:

    // Constructors
    ConfigData();
    ConfigData(std::string path);
};

#endif // __CONFIG_H__
