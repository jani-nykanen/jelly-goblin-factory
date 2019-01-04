// Configuration file routines
// (c) 2019 Jani Nykänen

#include "Config.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>


// Check if a comment line
static bool isCommentLine(std::string line) {

    for(int i = 0; i < line.length(); ++ i) {

        if(line[i] == '#') return true;
    }
    return false;
}


// Split words
static std::vector<std::string> splitWords(std::string line) {

    std::vector<std::string> ret = std::vector<std::string> ();
    std::string buffer = "";
    char c;
    bool started = false;
    bool isQuote = false;

    // Go through the characters
    for(int i = 0; i < line.length() && line[i] != '\n'; ++ i) {

        c = line[i];

        // Check if a quote
        if(c == '"') {

            isQuote = !isQuote;
            // Push
            if(started && !isQuote) {

                ret.push_back(buffer);
                buffer.clear();

                started = false;
            }
            else if(isQuote) {

                started = true;
            }
            continue;
        }
        else if(isQuote) {

            // Push a character
            started = true;
            buffer.push_back(c);

            continue;
        }

        // Check if not whitespace
        if(c != '\t' && c != ' ') {

            // Push a character
            started = true;
            buffer.push_back(c);
        }
        // If it is, may have to stop here
        else if(started) {

            ret.push_back(buffer);
            buffer.clear();

            started = false;
        }
    }

    // Push the remaining content, if any
    if(started) {

        ret.push_back(buffer);
    }

    return ret;
}


// Constructors
ConfigData::ConfigData() { /* ... */ }
ConfigData::ConfigData(std::string path) {

    params = std::vector<KeyValuePair> ();

    // Open file
    std::ifstream file(path.c_str());

    // Read lines
    std::string line;
    std::vector<std::string> splitRes;
    while (std::getline(file, line)) {

        // Check if comment
        if(isCommentLine(line))
            continue;

        // Split
        splitRes.clear();
        splitRes = splitWords(line);

        // Store parameters
        if(splitRes.size() >= 3) {

            // Make sure we have "="
            if(splitRes[1][0] != '=') {

                std::cout << "Warning in " << path << ": "
                          << "Symbol = expected, got: " << splitRes[1] << "\n";
            }
            else {

                // Store
                params.push_back(KeyValuePair(
                    splitRes[0],
                    splitRes[2]
                ));
            }
        }

    }

    // Close
    file.close();
}


// Get parameter
std::string ConfigData::getParam(std::string key, std::string def) {

    std::string ret = def;
    for(int i = 0; i < params.size(); ++ i) {

        if(params[i].key == key) {

            ret = params[i].value;
            break;
        }
    }
    return ret;
}
std::string ConfigData::getParam(std::string key) {

    return getParam(key, "");
}


// Get integer parameter
int ConfigData::getIntParam(std::string key, int def) {

    std::string r = getParam(key, "f");
    if(r == "f") {

        return def;
    }
    // Convert to integer
    int ret = 0;
    std::istringstream ( r ) >> ret;
    return ret;
}
