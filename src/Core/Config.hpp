// Configuration file routines
// (c) 2019 Jani Nykänen

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <vector>

#include "Types.hpp"


// Configuration data
class ConfigData {

private:

    // Parameters & their values
    std::vector<KeyValuePair> params;

public:

    // Constructors
    ConfigData();
    ConfigData(std::string path);

    // Get parameter
    std::string getParam(std::string key, std::string def);
    std::string getParam(std::string key);
    std::string getParam(int i);
    int getIntParam(std::string key, int def);
    float getFloatParam(std::string key, float def);

    // Get key
    std::string getKey(int i);

    // Get param count
    inline int getParamCount() {return (int)params.size();}
};

#endif // __CONFIG_H__
