// Uitility functions
// (c) 2019 Jani Nykänen

#include "Utility.hpp"

#include <sstream>

// Integer to string
std::string intToString(int a) {

    std::ostringstream out;
    out << a;
    return out.str();
}


// String to integer
int strToInt(std::string str) {

    int ret = 0;
    std::istringstream ( str ) >> ret;
    return ret;
}
