// A simple single-layer tilemap
// (NOTE: very ugly & simple, zero error
//  checking!)
// (c) 2019 Jani Nykänen

#include "Tilemap.hpp"

#include <fstream>
#include <stdexcept>
#include <cstdio>
#include <sstream>


// Find parameter value
static std::string findValue(std::string content, 
    std::string what) {

    std::string lookFor = what + "=\"";
    int p = content.find(lookFor) + lookFor.length();
    // Find the next quotation mark
    int i = p;
    for(; i < content.length(); ++ i) {

        if(content[i] == '"') {
            break;
        }
    }

    return content.substr(p,i-p);
}


// Parse properties
static void parseProperties(std::string content,
    std::vector<KeyValuePair> &properties) {

    // Find all the property positions
    std::vector<int> propPos;
    std::vector<int> propEnds;

    int p = 0;
    int oldP = 0;
    // Find property positions
    std::string find = "<property";
    while(true) {

        oldP = p;
        p = content.find(find, p+find.length());
        if(p <= oldP)
            break;

        // Push
        propPos.push_back(p + find.length());
    }

    // Find property keys & values
    // TODO: Inefficient with big data!
    std::string key, value;
    for(int i = 0; i < propPos.size(); ++ i) {

        key = findValue(content.substr(propPos[i]), "name");
        value = findValue(content.substr(propPos[i]), "value");

        // Store properties
        properties.push_back(KeyValuePair(key, value));
    }
}


// Parse CSV (to integers)
static void parseCSVInt(std::string content, 
    std::vector<int> &data) {

    std::string buffer = "";
    int count = 0;
    char c;
    for(int i = 0; i < content.size(); ++ i) {

        c = content[i];
        if(buffer.length() > 0 && c == ',') {

            if(count < data.size()) {
                
                std::istringstream(buffer) >> data[count ++];
                buffer = "";
            }
        }
        // Push to the buffer if not a whitespace
        else if(!(c == ' ' || c == '\n' || c == '\t')) {

            buffer.push_back(content[i]);
        }
    }
    if(buffer.length() > 0) {

         std::istringstream(buffer) >> data[count ++];
    }
}



// Constructor
Tilemap::Tilemap(std::string path) {

    // Read file to a string
    std::string content = "";
    std::ifstream file(path.c_str());
    if(file.is_open() == false) {

        throw std::runtime_error("Failed to open a file in " + path);
    }

    // Read lines
    std::string line;
    while (std::getline(file, line)) {

        content += line;
    }

    // Find dimensions
    std::istringstream(findValue(content,"width")) >> width;
    std::istringstream(findValue(content,"height")) >> height;

    // Parse properties
    properties = std::vector<KeyValuePair> ();
    parseProperties(content, properties);

    // Parse map data
    std::string findBegin = "<data encoding=\"csv\">";
    std::string findEnd = "</data>";
    int begin = content.find(findBegin) + findBegin.length();
    int end = content.find(findEnd);
    // Allocate memory
    data = std::vector<int> (width*height);
    // Parse CSV
    parseCSVInt(content.substr(begin, end-begin), data);
}


// Get tile
int Tilemap::getTile(int x, int y) {

    if(x < 0 || y < 0 || x >= width || y >= height)
        return -1;

    return data[y*width +x];
}


// Get a property
std::string Tilemap::getProp(std::string name) {

    for(int i = 0; i < properties.size(); ++ i) {

        if(properties[i].key == name) {

            return properties[i].value;
        }
    }
    return "0";
}
